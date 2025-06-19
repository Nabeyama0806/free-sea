#include "CharacterBase.h"
#include "SpriteActor.h"
#include "ReflectionBullet.h"
#include "StraightBullet.h"
#include "Model.h"
#include "ModelAnimation.h"
#include "ModelLoader.h"
#include "Camera.h"
#include "Stage.h"
#include "CircleCollider.h"
#include "SoundManager.h"
#include "InputSystem.h"
#include "Quaternion.h"
#include "Vector2.h"
#include "Time.h"
#include "Lerp.h"

//�R���X�g���N�^
CharacterBase::CharacterBase(
	const char* modelFilePath,
	Camera* camera,
	Stage* stage,
	const Vector3& position,
	int health,
	int playerIndex
) :
	ModelActor("Player"),
	m_camera(camera),
	m_stage(stage),
	m_maxHealth(health),
	m_health(health),
	m_playerIndex(playerIndex),
	m_spriteActor(nullptr),
	m_invincibleTime(0),
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
	m_model = new Model(modelFilePath, true);
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//�A�j���[�V�����̃t�@�C���p�X��n��
		m_model->Register(AnimeFileName[i]);
	}

	//�Փ˔���
	m_collider = new CircleCollider(Radius, Vector3(0, 50, 0));
}

//�X�V
void CharacterBase::Update()
{
	//�{���̍X�V
	ModelActor::Update();

	//���G���Ԃ̃J�E���g�_�E��
	if (m_invincibleTime > 0)
	{
		m_invincibleTime -= Time::GetInstance()->GetDeltaTime();
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

	//���͕����̎擾
	Vector2 input = InputSystem::GetInstance()->MoveValue(static_cast<InputSystem::ActionMap>(m_playerIndex));
	Vector3 move = Vector3(input.x, 0, input.y);

	//�ˏo�����̎擾
	if (!m_isShot)
	{
		float length = 80.0f;
		m_shotRotate = InputSystem::GetInstance()->RotationValue(static_cast<InputSystem::ActionMap>(m_playerIndex));
		if (!m_shotRotate.IsZero()) m_shotRotate.Normalize() *= length;
		else
		{
			Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
			m_shotRotate = forward;
		}
	}

	//�J�����̐��ʃx�N�g�����쐬
	Vector3 cameraForward = Vector3::Scale(m_camera->GetForward(), Vector3(1, 0, 1)).Normalized();

	//�J�����̌������l�������ړ���
	move = cameraForward * move.z + m_camera->GetRight() * move.x;

	//�ړ����Ă���Ƃ�
	if (!move.IsZero())
	{
		move.Normalize();
		m_transform.position += move * Speed;

		//���˒��͉�]���Ȃ�
		if (!m_isShot)
		{
			//�ˏo�������߂Ă���Ƃ�
			if (input.IsZero())
			{
				m_transform.rotation = Quaternion::Slerp(
					m_transform.rotation,
					Quaternion::LookRotation(GetShotForward()),
					0.2f);
			}
			else
			{
				m_transform.rotation = Quaternion::Slerp(
					m_transform.rotation,
					Quaternion::LookRotation(move),
					0.3f);
			}
			
		}
		else
		{
			if (!input.IsZero())
			{
				m_transform.rotation = Quaternion::Slerp(
					m_transform.rotation,
					Quaternion::LookRotation(GetShotForward()),
					0.2f);
			}
		}

		//�ړ��A�j���[�V�����̐ݒ�
		anime = Anime::Run;
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
	DrawLine3D(
		m_transform.position,
		m_transform.position + Vector3(m_shotRotate.x, 0, m_shotRotate.y),
		GetColor(255, 0, 0)
	);
	
	//�̗͕\��
	VECTOR scrPos = ConvWorldPosToScreenPos(Vector3(m_transform.position.x, 0, m_transform.position.z));
	float offsetX = m_maxHealth / 2.0f;
	DrawBoxAA(
		scrPos.x - offsetX,
		scrPos.y,
		scrPos.x + m_maxHealth - offsetX,
		scrPos.y + HealthSlideHeight,
		GetColor(50, 50, 55),
		false
	);

	//���G���Ԓ��͕\��/��\�����J��Ԃ��ē_�ł�����
	if (m_invincibleTime > 0)
	{
		//���G���Ԓ��̏����_���ʂ���Ȃ��\��
		if (static_cast<int>(m_invincibleTime * 10) % 2)
		{
			return;
		}
	}

	//�̗͕\��
	DrawBoxAA(
		scrPos.x - offsetX,
		scrPos.y,
		scrPos.x + m_health - offsetX,
		scrPos.y + HealthSlideHeight,
		GetColor(40, 255, 30),
		true
	);
}

//��e
void CharacterBase::Damage(int damage)
{
	//���G���Ԃ��Z�b�g
	m_invincibleTime = InvincibleTime;

	//�̗͂����炷
	m_health -= damage;

	//���񂾂�Փ˔���𖳂���
	if (m_health <= 0)
	{
		Destroy();
	}
}