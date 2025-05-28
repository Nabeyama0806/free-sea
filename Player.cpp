#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Quaternion.h"
#include "ModelLoader.h"
#include "ModelAnimation.h"

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

	//���͕����̎擾
	Vector3 move = Vector3(0, 0, 0);
	float speedRate = 1.0f;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_LSHIFT))	speedRate = DashSpeed;
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
		m_transform.position += move * Speed * speedRate;

		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(move),
			0.2f);

		animeIndex = static_cast<int>(Anime::Run);
	}
	
	m_model->PlayAnime(animeIndex);

	//�ڒn����
	m_isGrounded = MV1CollCheck_Line(m_mapModelHandle, -1, m_transform.position + RayPos, m_transform.position - RayPos).HitFlag == 1 ? true : false;

	if (!m_isGrounded) m_transform.position = SpawnPos;
}

void Player::Draw()
{
	ModelActor::Draw();
	if (!m_isGrounded) DrawLine3D(m_transform.position + RayPos, m_transform.position - RayPos, GetColor(255, 255, 0));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "HIT:%d", m_isGrounded);
}