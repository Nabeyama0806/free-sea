#pragma once
#include "BulletBase.h"

class StraightBullet : public BulletBase
{
private:
	static constexpr int MaxHealth = 1;			//反射できる回数(体力)
	static constexpr float AddForce = 1200.0f;	//投げる力

public:
	//コンストラクタ
	StraightBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		BulletBase(position, forward, stage, MaxHealth, AddForce)
	{
	}
};