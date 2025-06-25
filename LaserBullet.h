#pragma once
#pragma once
#include "Bullet.h"
#include "Stage.h"

class LaserBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//反射できる回数(体力)
	static constexpr int Power = 10;			//攻撃力
	static constexpr float AddForce = 750.0f;	//投げる力
	static constexpr float EraseTime = 10.0f;	//生存時間(秒)

public:
	//コンストラクタ
	LaserBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage)
	{
		//弾のステータスを設定
		m_health = MaxHealth;
		m_power = Power;
		m_addForce = AddForce;
		m_eraseTime = EraseTime;
	}

	static constexpr int BulletAmount = 1;			//一回で発射される弾の数
	static constexpr float ShotCoolTime = 0.1f;		//発射間隔
	static constexpr float BulletFiringRate = 0.1f;	//弾間の発射間隔
};