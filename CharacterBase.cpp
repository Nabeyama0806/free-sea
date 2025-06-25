#include "CharacterBase.h"
#include "Camera.h"
#include "Stage.h"
#include "ReflectionBullet.h"
#include "StraightBullet.h"
#include "DiffusionBullet.h"
#include "LaserBullet.h"
#include "Model.h"
#include "ModelAnimation.h"
#include "ModelLoader.h"
#include "SpriteActor.h"
#include "CircleCollider.h"
#include "SoundManager.h"
#include "InputSystem.h"
#include "Quaternion.h"
#include "Time.h"
#include "Lerp.h"

//コンストラクタ
CharacterBase::CharacterBase(
	const char* modelFilePath,
	const char* bulletFilePath,
	Camera* camera,
	Stage* stage,
	const Vector3& position,
	Bullet::Type bulletType,
	int playerIndex
) :
	ModelActor("Player"),
	BulletFilePath(bulletFilePath),
	m_camera(camera),
	m_stage(stage), 
	m_bulletType(bulletType),
	m_maxHealth(MaxHealth),
	m_health(MaxHealth),
	m_playerIndex(playerIndex),
	m_spriteActor(nullptr),
	m_flashTime(0),
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
	m_model = new Model(modelFilePath);
	for (int i = 0; i < static_cast<int>(Anime::Length); ++i)
	{
		//アニメーションのファイルパスを渡す
		m_model->Register(AnimeFileName[i]);
	}

	//衝突判定
	m_collider = new CircleCollider(Radius, Vector3(0, 50, 0));

	//弾
	switch (bulletType)
	{
	case Bullet::Type::Reflection:
		m_maxBulletAmount = ReflectionBullet::BulletAmount;
		m_shotCoolTime = ReflectionBullet::ShotCoolTime;
		m_bulletFiringRate = ReflectionBullet::BulletFiringRate;
		break;

	case Bullet::Type::Straight:
		m_maxBulletAmount = StraightBullet::BulletAmount;
		m_shotCoolTime = StraightBullet::ShotCoolTime;
		m_bulletFiringRate = StraightBullet::BulletFiringRate;
		break;

	case Bullet::Type::Diffusion:
		m_maxBulletAmount = DiffusionBullet::BulletAmount;
		m_shotCoolTime = DiffusionBullet::ShotCoolTime;
		m_bulletFiringRate = DiffusionBullet::BulletFiringRate;
		break;

	case Bullet::Type::Laser:
		m_maxBulletAmount = LaserBullet::BulletAmount;
		m_shotCoolTime = LaserBullet::ShotCoolTime;
		m_bulletFiringRate = LaserBullet::BulletFiringRate;

	default:
		break;
	}
}

//更新
void CharacterBase::Update()
{
	//本来の更新
	ModelActor::Update();

	//弾の発射
	BulletShot();

	//無敵時間のカウントダウン
	if (m_flashTime > 0)
	{
		m_flashTime -= Time::GetInstance()->GetDeltaTime();
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

	//前フレームの入力値を保存
	Vector2 prevInput = m_inputValue;
	
	//入力値の取得
	m_inputValue = InputSystem::GetInstance()->MoveValue(static_cast<InputSystem::ActionMap>(m_playerIndex));
	Vector3 move = Vector3(m_inputValue.x, 0, m_inputValue.y);

	//入力値がゼロの場合は前フレームの入力値を使用
	if (m_inputValue.IsZero()) m_inputValue = prevInput;

	//発射中は射出方向を更新しない
	if (!m_isShot) m_shotRotate = InputSystem::GetInstance()->RotationValue(static_cast<InputSystem::ActionMap>(m_playerIndex));

	//カメラの正面ベクトルを作成
	Vector3 cameraForward = Vector3::Scale(m_camera->GetForward(), Vector3(1, 0, 1)).Normalized();

	//カメラの向きを考慮した移動量
	move = cameraForward * move.z + m_camera->GetRight() * move.x;

	//移動しているとき
	if (!move.IsZero())
	{
		//移動
		move.Normalize();
		m_transform.position += move * Speed;

		//回転
		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(!m_isShot ? move : GetShotForward()),
			0.25f);

		//移動アニメーションの設定
		anime = Anime::Run;
	}
	else
	{
		//回転
		m_transform.rotation = Quaternion::Slerp(
			m_transform.rotation,
			Quaternion::LookRotation(m_shotRotate.IsZero() ? Vector3(m_inputValue.x, 0, m_inputValue.y) : GetShotForward()),
			0.25f);
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
	float length = 80.0f;
	DrawLine3D(
		m_transform.position,
		m_transform.position + Vector3(m_shotRotate.x * length, 0, m_shotRotate.y * length),
		GetColor(255, 0, 0)
	);
	
	//体力表示
	float offsetX = m_maxHealth / 2.0f;
	DrawBoxAA(
		HealthDrawPos[m_playerIndex].x - offsetX,
		HealthDrawPos[m_playerIndex].y,
		HealthDrawPos[m_playerIndex].x + m_maxHealth - offsetX,
		HealthDrawPos[m_playerIndex].y + HealthSlideHeight,
		GetColor(255, 0, 0),
		true
	);

	//無敵時間中は表示/非表示を繰り返して点滅させる
	if (m_flashTime > 0)
	{
		//無敵時間中の小数点第一位が奇数なら非表示
		if (static_cast<int>(m_flashTime * 10) % 2)
		{
			return;
		}
	}

	//体力表示
	DrawBoxAA(
		HealthDrawPos[m_playerIndex].x - offsetX,
		HealthDrawPos[m_playerIndex].y,
		HealthDrawPos[m_playerIndex].x + m_health - offsetX,
		HealthDrawPos[m_playerIndex].y + HealthSlideHeight,
		GetColor(40, 255, 30),
		true
	);
}

//弾の発射処理
void CharacterBase::BulletShot()
{
	//既に発射済み
	if (m_isShot)
	{
		//弾の発射間隔の経過時間
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//生成した弾の数を加算
		if (CreateBullet()) m_bulletInstanceAmount++;

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
	if (InputSystem::GetInstance()->BulletShot(static_cast<InputSystem::ActionMap>(m_playerIndex)))
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//弾の生成
bool CharacterBase::CreateBullet()
{
	//弾間の経過時間が発射レートを超えていれば弾を発射
	if (m_bulletElapsedTime > m_bulletFiringRate)
	{
		//経過時間のリセット
		m_bulletElapsedTime = 0;

		//正面から弾を発射する
		switch (m_bulletType)
		{
		case Bullet::Type::Reflection:
			AddChild(new ReflectionBullet(BulletFilePath, m_transform.position, GetShotForward(), m_stage));
			break;

		case Bullet::Type::Straight:
			AddChild(new StraightBullet(BulletFilePath, m_transform.position, GetShotForward(), m_stage));
			break;

		case Bullet::Type::Diffusion:
			//拡散弾の生成
			for (int i = 0; i < DiffusionBullet::DiffusionBulletAmount; ++i)
			{
				float angle = (i - (DiffusionBullet::DiffusionBulletAmount - 1) / 2.0f) * DiffusionBullet::AngleRate;
				Vector3 forward = Quaternion::AngleAxis(angle, Vector3(0, 1, 0)) * GetShotForward();
				AddChild(new DiffusionBullet(BulletFilePath, m_transform.position, forward, m_stage));
			}
			break;

		case Bullet::Type::Laser:
			AddChild(new LaserBullet(BulletFilePath, m_transform.position, GetShotForward(), m_stage));
			break;

		default:
			break;
		}

		//効果音の再生
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}

//被弾
void CharacterBase::Damage(int damage)
{
	//無敵時間をセット
	m_flashTime = FlashTime;

	//体力を減らす
	m_health -= damage;

	//死んだら衝突判定を無くす
	if (m_health <= 0)
	{
		Destroy();
	}
}