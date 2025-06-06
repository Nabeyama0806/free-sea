#include "PlayerBase.h"
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
PlayerBase::PlayerBase(
	Camera* camera,
	Stage* stage,
	const Vector3& position,
	PlayerBase::Bullet bullet,
	int playerIndex,
	int maxBulletAmount,
	float shotCoolTime,
	float bulletFiringRate
) :
	ModelActor("Player"),
	m_camera(camera),
	m_stage(stage),
	m_bullet(bullet),
	m_playerIndex(playerIndex),
	m_maxBulletAmount(maxBulletAmount),
	m_shotCoolTime(shotCoolTime),
	m_bulletFiringRate(bulletFiringRate),
	m_bulletElapsedTime(0),
	m_shotElapsedTime(0),
	m_isShot(false),
	m_isGrounded(false)
{
	//�p�����̒���
	m_transform.position = position;
	m_transform.scale = Scale;

	//�A�j���[�V�����̓o�^
	m_model = playerIndex == 0 ? new Model("Man/Man.mv1") : new Model("Man/Man2.mv1");
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//�A�j���[�V�����̃t�@�C���p�X��n��
		m_model->Register(AnimeFileName[i]);
	}

	m_collider = new CircleCollider(30);
}

//�X�V
void PlayerBase::Update()
{
	//�{���̍X�V
	ModelActor::Update();

	//�ړ�
	Anime anime = Anime::Idle;
	Move(anime);

	//�A�j���[�V�����̍Đ�
	m_model->PlayAnime(static_cast<int>(anime));

	//����
	BulletShot();
}

//�`��
void PlayerBase::Draw()
{
	//�{���̍X�V
	ModelActor::Draw();
}

//�ړ�
void PlayerBase::Move(Anime& anime)
{
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
	Vector3 move = Vector3(input.x, 0, -input.y);

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
			m_transform.rotation = Quaternion::Slerp(
				m_transform.rotation,
				Quaternion::LookRotation(move),
				0.1f);
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
}

//�e�̔���
void PlayerBase::BulletShot()
{
	//���ɔ��ˍς�
	if (m_isShot)
	{
		//�e�̔��ˊԊu�̌o�ߎ���
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//���������e�̐������Z
		if (BulletInstance()) m_bulletInstanceAmount++;

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
	if (InputSystem::GetInstance()->IsDecision(static_cast<InputSystem::ActionMap>(m_playerIndex)))
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//�e�̐���
bool PlayerBase::BulletInstance()
{
	//�e�Ԃ̌o�ߎ��Ԃ����˃��[�g�𒴂��Ă���Βe�𔭎�
	if (m_bulletElapsedTime > m_bulletFiringRate)
	{
		//�o�ߎ��Ԃ̃��Z�b�g
		m_bulletElapsedTime = 0;

		//���ʂ���e�𔭎˂���
		Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
		Vector3 instancePos = m_transform.position + BulletOffset + forward * 30;
		m_bullet == PlayerBase::Bullet::Straight ? AddChild(new StraightBullet(instancePos, forward, m_stage)) : AddChild(new ReflectionBullet(instancePos, forward, m_stage));

		//���ʉ��̍Đ�
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}