#pragma once
#include "ModelActor.h"
#include "Vector3.h"
#include "Vector2.h"

class Camera;
class Stage;

class CharacterBase : public ModelActor
{
public:
	enum class Type
	{
		BlueBird,
		GreenBird,

		Length,
	};

private:
	static constexpr float Scale = 3.0f;			//自身のサイズ
	static constexpr float Speed = 1.2f * Scale;	//自身のサイズに合せた移動速度
	static constexpr float Radius = 20.0f;			//衝突判定の半径
	static constexpr float InvincibleTime = 0.8f;	//無敵時間

	//アニメーションパターン
	enum class Anime
	{
		Idle,
		Run,

		Length,
	};

	//アニメーション配列
	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//待機
		"Man/Walking.mv1"	//移動
	};

protected:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);
	static constexpr Vector2 HealthSlidePos[2] =
	{
		Vector2(350, 100),
		Vector2(1400, 100),
	};
	static constexpr int HealthSlideHeight = 5;

	Camera* m_camera;
	Stage* m_stage;
	Vector2 m_shotRotate;
	int m_playerIndex;			//自身のプレイヤー番号
	float m_invincibleTime;		//残りの無敵時間
	bool m_isGrounded;			//床との接触判定
	bool m_isShot;				//発射中

	int m_bulletInstanceAmount;	//生成された弾の数
	float m_shotElapsedTime;	//発射間隔の経過時間
	float m_bulletElapsedTime;	//弾間の経過時間

	int m_maxHealth;			//最大体力
	int m_health;				//体力
	int	m_maxBulletAmount;		//一回で発射される弾の数
	float m_shotCoolTime;		//発射間隔
	float m_bulletFiringRate;	//弾間の発射間隔

	virtual void Update() override;	//更新
	virtual void Draw() override;	//描画

public:
	//コンストラクタ
	CharacterBase(
		const char* modelFilepath,
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		int health,
		int playerIndex
	);

	//被弾
	void Damage(int damage);

	//射出方向の取得
	Vector3 GetShotForward()
	{
		Vector3 tmp = Vector3(m_shotRotate.x, 0, m_shotRotate.y);
		if (!tmp.IsZero()) tmp.Normalize();
		return tmp;
	}

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) {};
};