#include "CharacterBase.h"
#include "Camera.h"
#include "Stage.h"
#include "ReflectionBullet.h"
#include "StraightBullet.h"
#include "DiffusionBullet.h"
#include "LaserBullet.h"
#include "Model.h"
#include "ModelAnimation.h"
#include "ModelLoader.h"
#include "SpriteActor.h"
#include "CircleCollider.h"
#include "SoundManager.h"
#include "InputSystem.h"
#include "Quaternion.h"
#include "Time.h"
#include "Lerp.h"

//�R���X�g���N�^
CharacterBase::CharacterBase(
	const char* modelFilePath,
	const char* bulletFilePath,
	Camera* camera,
	Stage* stage,
	const Vector3& position,
	Bullet::Type bulletType,
	int playerIndex
) :
	ModelActor("Player"),
	BulletFilePath(bulletFilePath),
	m_camera(camera),
	m_stage(stage), 
	m_bulletType(bulletType),
	m_maxHealth(MaxHealth),
	m_health(MaxHealth),
	m_playerIndex(playerIndex),
	m_spriteActor(nullptr),
	m_flashTime(0),
	m_maxBulletAmount(0),
	m_shotCoolTime(0),
	m_bulletFiringRate(0),
	m_bulletInstanceAmount(0),
	m_bulletElapsedTime(0),
	m_shotElapsedTime(0),
	m_isShot(false),
	m_isGrounded(false)
{
	//�p�����̒���
	m_transform.position = position;
	m_transform.scale = Scale;

	//�A�j���[�V�����̓o�^
	m_model = new Model(modelFilePath);
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//�A�j���[�V�����̃t�@�C���p�X��n��
		m_model->Register(AnimeFileName[i]);
	}

	//�Փ˔���
	m_collider = new CircleCollider(Radius, Vector3(0, 50, 0));

	//�e
	switch (bulletType)
	{
	case Bullet::Type::Reflection:
		m_maxBulletAmount = ReflectionBullet::BulletAmount;
		m_shotCoolTime = ReflectionBullet::ShotCoolTime;
		m_bulletFiringRate = ReflectionBullet::BulletFiringRate;
		break;

	case Bullet::Type::Straight:
		m_maxBulletAmount = StraightBullet::BulletAmount;
		m_shotCoolTime = StraightBullet::ShotCoolTime;
		m_bulletFiringRate = StraightBullet::BulletFiringRate;
		break;

	case Bullet::Type::Diffusion:
		m_maxBulletAmount = DiffusionBullet::BulletAmount;
		m_shotCoolTime = DiffusionBullet::ShotCoolTime;
		m_bulletFiringRate = DiffusionBullet::BulletFiringRate;
		break;

	case Bullet::Type::Laser:
		m_maxBulletAmount = LaserBullet::BulletAmount;
		m_shotCoolTime = LaserBullet::ShotCoolTime;
		m_bulletFiringRate = LaserBullet::BulletFiringRate;

	default:
		break;
	}
}

//�X�V
void CharacterBase::Update()
{
	//�{���̍X�V
	ModelActor::Update();

	//�e�̔���
	BulletShot();

	//���G���Ԃ̃J�E���g�_�E��
	if (m_flashTime > 0)
	{
		m_flashTime -= Time::GetInstance()->GetDeltaTime();
	}

	//�A�j���[�V����
	Anime anime = Anime::Idle;

	//�ړ��O�̍��W
	Vector3 prevPos = m_transform.position;

	//�ړ��O�̏������擾
	MV1_COLL_RESULT_POLY prevPoly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		prevPos + Vector3(0, 100, 0),
		prevPos - Vector3(0, 100, 0));

	//�O�t���[���̓��͒l��ۑ�
	Vector2 prevInput = m_inputValue;
	
	//���͒l�̎擾
	m_inputValue = InputSystem::GetInstance()->MoveValue(static_cast<InputSystem::ActionMap>(m_playerIndex));
	Vector3 move = Vector3(m_inputValue.x, 0, m_inputValue.y);

	//���͒l���[���̏ꍇ�͑O�t���[���̓��͒l���g�p
	if (m_inputValue.IsZero()) m_inputValue = prevInput;

	//���˒��͎ˏo�������X�V���Ȃ�
	if (!m_isShot) m_shotRotate = InputSystem::GetInstance()->RotationValue(static_cast<InputSystem::ActionMap>(m_playerIndex));

	//�J�����̐��ʃx�N�g�����쐬
	Vector3 cameraForward = Vector3::Scale(m_camera->GetForward(), Vector3(1, 0, 1)).Normalized();

	//�J�����̌������l�������ړ���
	move = cameraForward * move.z + m_camera->GetRight() * move.x;

	//�ړ����Ă���Ƃ�
	if (!move.IsZero())
	{
		//�ړ�
		move.Normalize();
		m_transform.position += move * Speed;

		//��]
		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(!m_isShot ? move : GetShotForward()),
			0.25f);

		//�ړ��A�j���[�V�����̐ݒ�
		anime = Anime::Run;
	}
	else
	{
		//��]
		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(m_shotRotate.IsZero() ? Vector3(m_inputValue.x, 0, m_inputValue.y) : GetShotForward()),
			0.25f);
	}

	// �ړ���̏������擾
	MV1_COLL_RESULT_POLY poly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		m_transform.position + Vector3(0, 100, 0),
		m_transform.position - Vector3(0, 100, 0));

	// ���𓥂݊O���Ă���H
	if (!poly.HitFlag)
	{
		int index = 0;
		while (index < 3)
		{
			// ���|���S���̎O�p�`�̂����A�ǂ̕ӂ��ׂ��ł��邩�𒲂ׂ�
			int toIndex = index + 1 != 3 ? index + 1 : 0;

			// �������m�̌�������
			Vector2 a(prevPos.x, prevPos.z);
			Vector2 b(m_transform.position.x, m_transform.position.z);
			Vector2 c(prevPoly.Position[index].x, prevPoly.Position[index].z);
			Vector2 d(prevPoly.Position[toIndex].x, prevPoly.Position[toIndex].z);

			Vector2 ab = b - a;
			Vector2 cd = d - c;
			Vector2 ca = a - c;

			index++;

			// ���������s�H
			if (Vector2::Cross(cd, ab) == 0)
			{
				continue;
			}

			// �������m�̌����_���v�Z
			// t��0�`1�̊Ԃł���ΐ������m���������Ă���
			float t = Vector2::Cross(-cd, ca) / Vector2::Cross(cd, ab);
			if (t < 0 || 1 < t)
			{
				continue;
			}

			// �������W���v�Z
			Vector2 crossPos = Lerp::Exec(a, b, t);

			// �ǂ�������邽�߂ɁA�ړ��悩��ӂ̍ŋߓ_���v�Z
			Vector2 cpcN = (c - crossPos).Normalize();
			Vector2 x = crossPos + (cpcN * Vector2::Dot(cpcN, b - crossPos));

			// �ӏゾ��MV1CollCheck_Line�̔��肩��O��Ă��܂��ꍇ�����邽�߁A�ق�̏����]�v�ɖ߂�
			x += (x - b).Normalize() * 0.01f;

			// �����������W�ֈړ�
			m_transform.position = Vector3(x.x, 0, x.y);

			// ������̍��W�ł����ɏ��Ȃ��ꍇ�͈ړ����Ȃ��������Ƃɂ���
			if (!MV1CollCheck_Line(
				m_stage->GetModelHandle(),
				m_stage->GetFrameIndex(),
				m_transform.position + Vector3(0, 100, 0),
				m_transform.position - Vector3(0, 100, 0)).HitFlag)
			{
				m_transform.position = prevPos;
			}
			break;
		}
	}
		
	//�A�j���[�V�����̍Đ�
	m_model->PlayAnime(static_cast<int>(anime));
}

//�`��
void CharacterBase::Draw()
{
	//�{���̍X�V
	ModelActor::Draw();

	//�ˏo�����̕`��
	float length = 80.0f;
	DrawLine3D(
		m_transform.position,
		m_transform.position + Vector3(m_shotRotate.x * length, 0, m_shotRotate.y * length),
		GetColor(255, 0, 0)
	);
	
	//�̗͕\��
	float offsetX = m_maxHealth / 2.0f;
	DrawBoxAA(
		HealthDrawPos[m_playerIndex].x - offsetX,
		HealthDrawPos[m_playerIndex].y,
		HealthDrawPos[m_playerIndex].x + m_maxHealth - offsetX,
		HealthDrawPos[m_playerIndex].y + HealthSlideHeight,
		GetColor(255, 0, 0),
		true
	);

	//���G���Ԓ��͕\��/��\�����J��Ԃ��ē_�ł�����
	if (m_flashTime > 0)
	{
		//���G���Ԓ��̏����_���ʂ���Ȃ��\��
		if (static_cast<int>(m_flashTime * 10) % 2)
		{
			return;
		}
	}

	//�̗͕\��
	DrawBoxAA(
		HealthDrawPos[m_playerIndex].x - offsetX,
		HealthDrawPos[m_playerIndex].y,
		HealthDrawPos[m_playerIndex].x + m_health - offsetX,
		HealthDrawPos[m_playerIndex].y + HealthSlideHeight,
		GetColor(40, 255, 30),
		true
	);
}

//�e�̔��ˏ���
void CharacterBase::BulletShot()
{
	//���ɔ��ˍς�
	if (m_isShot)
	{
		//�e�̔��ˊԊu�̌o�ߎ���
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//���������e�̐������Z
		if (CreateBullet()) m_bulletInstanceAmount++;

		//�ő吔�܂Ő���������t���O��܂�
		if (m_bulletInstanceAmount == m_maxBulletAmount)
		{
			m_isShot = false;
			m_bulletInstanceAmount = 0;
		}
	}

	//���˂̓��͎�t�̌o�ߎ���
	m_shotElapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_shotElapsedTime < m_shotCoolTime) return;

	//���˃{�^���������ꂽ��e�𐶐�
	if (InputSystem::GetInstance()->BulletShot(static_cast<InputSystem::ActionMap>(m_playerIndex)))
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//�e�̐���
bool CharacterBase::CreateBullet()
{
	//�e�Ԃ̌o�ߎ��Ԃ����˃��[�g�𒴂��Ă���Βe�𔭎�
	if (m_bulletElapsedTime > m_bulletFiringRate)
	{
		//�o�ߎ��Ԃ̃��Z�b�g
		m_bulletElapsedTime = 0;

		//���ʂ���e�𔭎˂���
		switch (m_bulletType)
		{
		case Bullet::Type::Reflection:
			AddChild(new ReflectionBullet(BulletFilePath, m_transform.position, GetShotForward(), m_stage));
			break;

		case Bullet::Type::Straight:
			AddChild(new StraightBullet(BulletFilePath, m_transform.position, GetShotForward(), m_stage));
			break;

		case Bullet::Type::Diffusion:
			//�g�U�e�̐���
			for (int i = 0; i < DiffusionBullet::DiffusionBulletAmount; ++i)
			{
				float angle = (i - (DiffusionBullet::DiffusionBulletAmount - 1) / 2.0f) * DiffusionBullet::AngleRate;
				Vector3 forward = Quaternion::AngleAxis(angle, Vector3(0, 1, 0)) * GetShotForward();
				AddChild(new DiffusionBullet(BulletFilePath, m_transform.position, forward, m_stage));
			}
			break;

		case Bullet::Type::Laser:
			AddChild(new LaserBullet(BulletFilePath, m_transform.position, GetShotForward(), m_stage));
			break;

		default:
			break;
		}

		//���ʉ��̍Đ�
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}

//��e
void CharacterBase::Damage(int damage)
{
	//���G���Ԃ��Z�b�g
	m_flashTime = FlashTime;

	//�̗͂����炷
	m_health -= damage;

	//���񂾂�Փ˔���𖳂���
	if (m_health <= 0)
	{
		Destroy();
	}
}