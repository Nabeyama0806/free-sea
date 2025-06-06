#pragma once
#include "ModelActor.h"
#include "Vector3.h"

class Camera;
class Stage;

class PlayerBase : public ModelActor
{
public:
	enum class Bullet
	{
		Straight,
		Reflect,
	};

private:
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
		"Man/Sprint.mv1"	//移動
	};

private:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);
	static constexpr float Scale = 3.0f;			//自身のサイズ
	static constexpr float Speed = 1.2f * Scale;	//自身のサイズに合せた移動速度
	static constexpr float Radius = 20.0f;			//衝突判定の半径

	Camera* m_camera;
	Stage* m_stage;
	Bullet m_bullet;
	int m_playerIndex;			//自身のプレイヤー番号
	bool m_isGrounded;			//床との接触判定
	bool m_isShot;				//発射中

	//弾
	int	m_maxBulletAmount;		//一回で発射される弾の数
	float m_shotCoolTime;		//発射間隔
	float m_bulletFiringRate;	//弾間の発射間隔

	int m_bulletInstanceAmount;	//生成された弾の数
	float m_shotElapsedTime;	//発射間隔の経過時間
	float m_bulletElapsedTime;	//弾間の経過時間

	void Move(Anime& anime);		//移動
	void BulletShot();				//発射
	bool BulletInstance();			//弾の生成

protected:
	virtual void Update() override;	//更新
	virtual void Draw() override;

public:
	//コンストラクタ
	PlayerBase(
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		Bullet bullet,
		int playerIndex,
		int maxBulletAmount,
		float shotCoolTime,
		float bulletFiringRate
	);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) {};
};