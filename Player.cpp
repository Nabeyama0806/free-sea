#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Quaternion.h"
#include "ModelLoader.h"
#include "ModelAnimation.h"

//コンストラクタ
Player::Player(Camera* camera, int mapModelHandle) :
	ModelActor("Player"),
	m_camera(camera),
	m_isGrounded(false),
	m_mapModelHandle(mapModelHandle)
{
	//アニメーションの登録
	m_model = new Model("Man/Man.mv1");
	for (int i = 0; i < AnimeAmount; ++i)
	{
		//アニメーションのファイルパスを渡す
		m_model->Register(AnimeFileName[i]);
	}

	//姿勢情報の調整
	m_transform.position = SpawnPos;
	m_transform.scale = Scale;
}

//更新
void Player::Update()
{
	//本来の更新
	ModelActor::Update();

	//入力方向の取得
	Vector3 move = Vector3(0, 0, 0);
	float speedRate = 1.0f;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_LSHIFT))	speedRate = DashSpeed;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_W)) move.z =  1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_S)) move.z = -1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_D)) move.x =  1;
	if (Input::GetInstance()->IsKeyPress(KEY_INPUT_A)) move.x = -1;

	//カメラの正面ベクトルを作成
	Vector3 cameraForward = Vector3::Scale(m_camera->GetForward(), Vector3(1, 0, 1)).Normalized();

	//カメラの向きを考慮した移動量
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

	//接地判定
	m_isGrounded = MV1CollCheck_Line(m_mapModelHandle, -1, m_transform.position + RayPos, m_transform.position - RayPos).HitFlag == 1 ? true : false;

	if (!m_isGrounded) m_transform.position = SpawnPos;
}

void Player::Draw()
{
	ModelActor::Draw();
	if (!m_isGrounded) DrawLine3D(m_transform.position + RayPos, m_transform.position - RayPos, GetColor(255, 255, 0));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "HIT:%d", m_isGrounded);
}