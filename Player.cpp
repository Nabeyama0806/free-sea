#include "Player.h"
#include "Bullet.h"
#include "Input.h"
#include "Time.h"
#include "Quaternion.h"
#include "ModelLoader.h"
#include "ModelAnimation.h"
#include "SoundManager.h"
#include "Lerp.h"
#include "Vector2.h"
#include "Debug.h"

//�R���X�g���N�^
Player::Player(Camera* camera, int mapModelHandle) :
	ModelActor("Player"),
	m_camera(camera),
	m_mapModelHandle(mapModelHandle),
	m_bulletInstanceAmount(0),
	m_shotElapsedTime(ShotCoolTime),
	m_bulletElapsedTime(0),
	m_isShot(false),
	m_isGrounded(false)
{
	//�A�j���[�V�����̓o�^
	m_model = new Model("Man/Man.mv1");
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//�A�j���[�V�����̃t�@�C���p�X��n��
		m_model->Register(AnimeFileName[i]);
	}

	//�p�����̒���
	m_transform.position = SpawnPos;
	m_transform.scale = Scale;
}

//�X�V
void Player::Update()
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
void Player::Draw()
{
	ModelActor::Draw();
#ifdef _DEBUG
	DrawSphere3D(m_transform.position, Radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
#endif
}

//�ړ�
void Player::Move(Anime& anime)
{
	//�ړ��O�̍��W
	Vector3 prevPos = m_transform.position;

	//���͕����̎擾
	Vector3 move = Vector3(0, 0, 0);
	if (Input::GetInstance()->MoveUp())    move.z = 1;
	if (Input::GetInstance()->MoveDown())  move.z = -1;
	if (Input::GetInstance()->MoveRight()) move.x = 1;
	if (Input::GetInstance()->MoveLeft())  move.x = -1;

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
				0.2f);
		}

		//�ړ��A�j���[�V�����̐ݒ�
		anime = Anime::Run;
	}

	// �ڒn����
	MV1_COLL_RESULT_POLY_DIM coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, Radius);
	m_isGrounded = coll.HitNum >= 1 ? true : false;

	// �ڒn���Ă��Ȃ����A���ړ����͂����鎞
	if (m_isGrounded && !move.IsZero())
	{
		//�i�[�p
		Vector3 slide;

		//�ǂ̖@���x�N�g�����擾
		VECTOR normal = coll.Dim[0].Normal;
		Vector3 wallNormal(normal.x, normal.y, normal.z);

		// �ǂɉ����Ĉړ�
		Vector3 tmp = -move.Normalize() * 0.01f;
		Vector3::WallSlipVector(&slide, move, wallNormal);
		m_transform.position -= move * Speed + tmp;
		m_transform.position += slide * Speed;
	}

	////������̍��W�ł��͈͊O�ɂ���Έړ����Ȃ��������Ƃɂ���
	//coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, Radius);
	//m_isGrounded = coll.HitNum >= 1 ? true : false;
	//if (!m_isGrounded)
	//{
	//	m_transform.position = prevPos;
	//}
}

//�e�̔���
void Player::BulletShot()
{
	//���ɔ��ˍς�
	if (m_isShot)
	{
		//�e�̔��ˊԊu�̌o�ߎ���
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//���������e�̐������Z
		if (BulletInstance()) m_bulletInstanceAmount++;

		//�ő吔�܂Ő���������t���O��܂�
		if (m_bulletInstanceAmount == BulletAmount)
		{
			m_isShot = false;
			m_bulletInstanceAmount = 0;
		}
	}

	//���˂̓��͎�t�̌o�ߎ���
	m_shotElapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_shotElapsedTime < ShotCoolTime) return;

	//���˃{�^���������ꂽ��e�𐶐�
	if (Input::GetInstance()->IsDecision())
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//�e�̐���
bool Player::BulletInstance()
{
	//�e�Ԃ̌o�ߎ��Ԃ����˃��[�g�𒴂��Ă���Βe�𔭎�
	if (m_bulletElapsedTime > BulletFiringRate)
	{
		//�o�ߎ��Ԃ̃��Z�b�g
		m_bulletElapsedTime = 0;

		//���ʂ���e�𔭎˂���
		Vector3 forward = m_transform.rotation * Vector3(0, 0, -1).Normalized();
		AddChild(new Bullet(m_transform.position + BulletPosOffset, forward, this));

		//���ʉ��̍Đ�
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}
