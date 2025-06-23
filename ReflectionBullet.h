#pragma once
#include "Bullet.h"
#include "Stage.h"

class ReflectionBullet : public Bullet
{
private:
	static constexpr int Power = 20;			//攻撃力
	static constexpr float AddForce = 500.0f;	//投げる力

public:
	//コンストラクタ
	ReflectionBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage)
	{
		//弾のステータスを設定
		m_power = Power;
		m_addForce = AddForce;
	}

	static constexpr int BulletAmount = 5;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 1.4f;			//発射間隔
	static constexpr float BulletFiringRate = 0.25f;	//弾間の発射間隔
};