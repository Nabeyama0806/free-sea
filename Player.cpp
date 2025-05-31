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

//コンストラクタ
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
	//アニメーションの登録
	m_model = new Model("Man/Man.mv1");
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
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

	//移動
	Anime anime = Anime::Idle;
	Move(anime);

	//アニメーションの再生
	m_model->PlayAnime(static_cast<int>(anime));

	//発射
	BulletShot();
}

//描画
void Player::Draw()
{
	ModelActor::Draw();
#ifdef _DEBUG
	DrawSphere3D(m_transform.position, Radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
#endif
}

//移動
void Player::Move(Anime& anime)
{
	//移動前の座標
	Vector3 prevPos = m_transform.position;

	//入力方向の取得
	Vector3 move = Vector3(0, 0, 0);
	if (Input::GetInstance()->MoveUp())    move.z = 1;
	if (Input::GetInstance()->MoveDown())  move.z = -1;
	if (Input::GetInstance()->MoveRight()) move.x = 1;
	if (Input::GetInstance()->MoveLeft())  move.x = -1;

	//カメラの正面ベクトルを作成
	Vector3 cameraForward = Vector3::Scale(m_camera->GetForward(), Vector3(1, 0, 1)).Normalized();

	//カメラの向きを考慮した移動量
	move = cameraForward * move.z + m_camera->GetRight() * move.x;

	//移動しているとき
	if (!move.IsZero())
	{
		move.Normalize();
		m_transform.position += move * Speed;

		//発射中は回転しない
		if (!m_isShot)
		{
			m_transform.rotation = Quaternion::Slerp(
				m_transform.rotation,
				Quaternion::LookRotation(move),
				0.2f);
		}

		//移動アニメーションの設定
		anime = Anime::Run;
	}

	// 接地判定
	MV1_COLL_RESULT_POLY_DIM coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, Radius);
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
		Vector3 tmp = -move.Normalize() * 0.01f;
		Vector3::WallSlipVector(&slide, move, wallNormal);
		m_transform.position -= move * Speed + tmp;
		m_transform.position += slide * Speed;
	}

	////調整後の座標でも範囲外にいれば移動をなかったことにする
	//coll = MV1CollCheck_Sphere(m_mapModelHandle, -1, m_transform.position, Radius);
	//m_isGrounded = coll.HitNum >= 1 ? true : false;
	//if (!m_isGrounded)
	//{
	//	m_transform.position = prevPos;
	//}
}

//弾の発射
void Player::BulletShot()
{
	//既に発射済み
	if (m_isShot)
	{
		//弾の発射間隔の経過時間
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//生成した弾の数を加算
		if (BulletInstance()) m_bulletInstanceAmount++;

		//最大数まで生成したらフラグを折る
		if (m_bulletInstanceAmount == BulletAmount)
		{
			m_isShot = false;
			m_bulletInstanceAmount = 0;
		}
	}

	//発射の入力受付の経過時間
	m_shotElapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_shotElapsedTime < ShotCoolTime) return;

	//発射ボタンが押されたら弾を生成
	if (Input::GetInstance()->IsDecision())
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//弾の生成
bool Player::BulletInstance()
{
	//弾間の経過時間が発射レートを超えていれば弾を発射
	if (m_bulletElapsedTime > BulletFiringRate)
	{
		//経過時間のリセット
		m_bulletElapsedTime = 0;

		//正面から弾を発射する
		Vector3 forward = m_transform.rotation * Vector3(0, 0, -1).Normalized();
		AddChild(new Bullet(m_transform.position + BulletPosOffset, forward, this));

		//効果音の再生
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}
