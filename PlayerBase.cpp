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

//コンストラクタ
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
	//姿勢情報の調整
	m_transform.position = position;
	m_transform.scale = Scale;

	//アニメーションの登録
	m_model = playerIndex == 0 ? new Model("Man/Man.mv1") : new Model("Man/Man2.mv1");
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//アニメーションのファイルパスを渡す
		m_model->Register(AnimeFileName[i]);
	}

	m_collider = new CircleCollider(30);
}

//更新
void PlayerBase::Update()
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
void PlayerBase::Draw()
{
	//本来の更新
	ModelActor::Draw();
}

//移動
void PlayerBase::Move(Anime& anime)
{
	//移動前の座標
	Vector3 prevPos = m_transform.position;

	//移動前の床情報を取得
	MV1_COLL_RESULT_POLY prevPoly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		prevPos + Vector3(0, 100, 0),
		prevPos - Vector3(0, 100, 0));

	//入力方向の取得
	Vector2 input = InputSystem::GetInstance()->MoveValue(static_cast<InputSystem::ActionMap>(m_playerIndex));
	Vector3 move = Vector3(input.x, 0, -input.y);

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
				0.1f);
		}

		//移動アニメーションの設定
		anime = Anime::Run;
	}

	// 移動後の床情報を取得
	MV1_COLL_RESULT_POLY poly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		m_transform.position + Vector3(0, 100, 0),
		m_transform.position - Vector3(0, 100, 0));

	// 床を踏み外している？
	if (!poly.HitFlag)
	{
		int index = 0;
		while (index < 3)
		{
			// 床ポリゴンの三角形のうち、どの辺を跨いでいるかを調べる
			int toIndex = index + 1 != 3 ? index + 1 : 0;

			// 線分同士の交差判定
			Vector2 a(prevPos.x, prevPos.z);
			Vector2 b(m_transform.position.x, m_transform.position.z);
			Vector2 c(prevPoly.Position[index].x, prevPoly.Position[index].z);
			Vector2 d(prevPoly.Position[toIndex].x, prevPoly.Position[toIndex].z);

			Vector2 ab = b - a;
			Vector2 cd = d - c;
			Vector2 ca = a - c;

			index++;

			// 線分が平行？
			if (Vector2::Cross(cd, ab) == 0)
			{
				continue;
			}

			// 線分同士の交差点を計算
			// tが0～1の間であれば線分同士が交差している
			float t = Vector2::Cross(-cd, ca) / Vector2::Cross(cd, ab);
			if (t < 0 || 1 < t)
			{
				continue;
			}

			// 交差座標を計算
			Vector2 crossPos = Lerp::Exec(a, b, t);

			// 壁ずりをするために、移動先から辺の最近点を計算
			Vector2 cpcN = (c - crossPos).Normalize();
			Vector2 x = crossPos + (cpcN * Vector2::Dot(cpcN, b - crossPos));

			// 辺上だとMV1CollCheck_Lineの判定から外れてしまう場合があるため、ほんの少し余計に戻す
			x += (x - b).Normalize() * 0.01f;

			// 調整した座標へ移動
			m_transform.position = Vector3(x.x, 0, x.y);

			// 調整後の座標でも床に乗れない場合は移動をなかったことにする
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

//弾の発射
void PlayerBase::BulletShot()
{
	//既に発射済み
	if (m_isShot)
	{
		//弾の発射間隔の経過時間
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//生成した弾の数を加算
		if (BulletInstance()) m_bulletInstanceAmount++;

		//最大数まで生成したらフラグを折る
		if (m_bulletInstanceAmount == m_maxBulletAmount)
		{
			m_isShot = false;
			m_bulletInstanceAmount = 0;
		}
	}

	//発射の入力受付の経過時間
	m_shotElapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_shotElapsedTime < m_shotCoolTime) return;

	//発射ボタンが押されたら弾を生成
	if (InputSystem::GetInstance()->IsDecision(static_cast<InputSystem::ActionMap>(m_playerIndex)))
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//弾の生成
bool PlayerBase::BulletInstance()
{
	//弾間の経過時間が発射レートを超えていれば弾を発射
	if (m_bulletElapsedTime > m_bulletFiringRate)
	{
		//経過時間のリセット
		m_bulletElapsedTime = 0;

		//正面から弾を発射する
		Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
		Vector3 instancePos = m_transform.position + BulletOffset + forward * 30;
		m_bullet == PlayerBase::Bullet::Straight ? AddChild(new StraightBullet(instancePos, forward, m_stage)) : AddChild(new ReflectionBullet(instancePos, forward, m_stage));

		//効果音の再生
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}