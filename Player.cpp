#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Quaternion.h"
#include "ModelLoader.h"
#include "ModelAnimation.h"
#include "Lerp.h"
#include "Vector2.h"

#include "Debug.h"

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

	//移動前の座標
	Vector3 prevPos = m_transform.position;

	//入力方向の取得
	Vector3 move = Vector3(0, 0, 0);
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
		m_transform.position += move * Speed;

		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(move),
			0.2f);

		animeIndex = static_cast<int>(Anime::Run);
	}
	
	m_model->PlayAnime(animeIndex);

	// 接地判定
	MV1_COLL_RESULT_POLY_DIM coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, 50);
	m_isGrounded = coll.HitNum >= 1 ? true : false;

	// 接地していない時、かつ移動入力がある時
	if (m_isGrounded && !move.IsZero()) 
	{
		//格納用
		Vector3 slide;

		//壁の法線ベクトルを取得
		VECTOR normal = coll.Dim[0].Normal;
		Vector3 wallNormal(normal.x, normal.y, normal.z);

		// 壁に沿って移動
		Vector3 tmp = move.Normalize() * 0.01f;
		Vector3::WallSlipVector(&slide, move, wallNormal);
		m_transform.position -= move * Speed + tmp;
		m_transform.position += slide * Speed;
	}

	//調整後の座標でも範囲外にいれば移動をなかったことにする
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