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

//コンストラクタ
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
	//姿勢情報の調整
	m_transform.position = position;
	m_transform.scale = Scale;

	//アニメーションの登録
	m_model = new Model(modelFilePath, true);
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//アニメーションのファイルパスを渡す
		m_model->Register(AnimeFileName[i]);
	}

	//衝突判定
	m_collider = new CircleCollider(Radius, Vector3(0, 50, 0));
}

//更新
void CharacterBase::Update()
{
	//本来の更新
	ModelActor::Update();

	//無敵時間のカウントダウン
	if (m_invincibleTime > 0)
	{
		m_invincibleTime -= Time::GetInstance()->GetDeltaTime();
	}

	//アニメーション
	Anime anime = Anime::Idle;

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
	Vector3 move = Vector3(input.x, 0, input.y);

	//射出方向の取得
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
			//射出方向を定めているとき
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
		
	//アニメーションの再生
	m_model->PlayAnime(static_cast<int>(anime));
}

//描画
void CharacterBase::Draw()
{
	//本来の更新
	ModelActor::Draw();

	//射出方向の描画
	DrawLine3D(
		m_transform.position,
		m_transform.position + Vector3(m_shotRotate.x, 0, m_shotRotate.y),
		GetColor(255, 0, 0)
	);
	
	//体力表示
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

	//無敵時間中は表示/非表示を繰り返して点滅させる
	if (m_invincibleTime > 0)
	{
		//無敵時間中の小数点第一位が奇数なら非表示
		if (static_cast<int>(m_invincibleTime * 10) % 2)
		{
			return;
		}
	}

	//体力表示
	DrawBoxAA(
		scrPos.x - offsetX,
		scrPos.y,
		scrPos.x + m_health - offsetX,
		scrPos.y + HealthSlideHeight,
		GetColor(40, 255, 30),
		true
	);
}

//被弾
void CharacterBase::Damage(int damage)
{
	//無敵時間をセット
	m_invincibleTime = InvincibleTime;

	//体力を減らす
	m_health -= damage;

	//死んだら衝突判定を無くす
	if (m_health <= 0)
	{
		Destroy();
	}
}