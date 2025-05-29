#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Quaternion.h"
#include "ModelLoader.h"
#include "ModelAnimation.h"
#include "Lerp.h"
#include "Vector2.h"

#include "Debug.h"

//�R���X�g���N�^
Player::Player(Camera* camera, int mapModelHandle) :
	ModelActor("Player"),
	m_camera(camera),
	m_isGrounded(false),
	m_mapModelHandle(mapModelHandle)
{
	//�A�j���[�V�����̓o�^
	m_model = new Model("Man/Man.mv1");
	for (int i = 0; i < AnimeAmount; ++i)
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

	//�ړ��O�̍��W
	Vector3 prevPos = m_transform.position;

	//���͕����̎擾
	Vector3 move = Vector3(0, 0, 0);
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_W)) move.z =  1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_S)) move.z = -1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_D)) move.x =  1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_A)) move.x = -1;

	//�J�����̐��ʃx�N�g�����쐬
	Vector3 cameraForward = Vector3::Scale(m_camera->GetForward(), Vector3(1, 0, 1)).Normalized();

	//�J�����̌������l�������ړ���
	move = cameraForward * move.z + m_camera->GetRight() * move.x;

	int animeIndex = static_cast<int>(Anime::Idle);
	if (!move.IsZero())
	{
		move.Normalize();
		m_transform.position += move * Speed;

		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(move),
			0.2f);

		animeIndex = static_cast<int>(Anime::Run);
	}
	
	m_model->PlayAnime(animeIndex);

	// �ڒn����
	MV1_COLL_RESULT_POLY_DIM coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, 50);
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
		Vector3 tmp = move.Normalize() * 0.01f;
		Vector3::WallSlipVector(&slide, move, wallNormal);
		m_transform.position -= move * Speed + tmp;
		m_transform.position += slide * Speed;
	}

	//������̍��W�ł��͈͊O�ɂ���Έړ����Ȃ��������Ƃɂ���
	coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, 50);
	m_isGrounded = coll.HitNum >= 1 ? true : false;
	if (!m_isGrounded)
	{
		m_transform.position = prevPos;
	}
}

void Player::Draw()
{
	ModelActor::Draw();
#ifdef _DEBUG
	DrawSphere3D(m_transform.position, 50, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "HIT:%d", m_isGrounded);
#endif

}