#pragma once
#include "Bullet.h"
#include "DxLib.h"

class StraightBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//反射できる回数(体力)
	static constexpr int Power = 50;			//攻撃力
	static constexpr float AddForce = 950.0f;	//投げる力

public:
	//コンストラクタ
	StraightBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage)
	{
		//弾のステータスを設定
		m_health = MaxHealth;
		m_power = Power;
		m_addForce = AddForce;
	}

	static constexpr int BulletAmount = 2;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 1.0f;			//発射間隔
	static constexpr float BulletFiringRate = 0.3f;		//弾間の発射間隔
};