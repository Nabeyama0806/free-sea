#pragma once
#include "Bullet.h"
#include "Stage.h"

class ReflectionBullet : public Bullet
{
private:
	static constexpr int Power = 13;			//攻撃力
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
};