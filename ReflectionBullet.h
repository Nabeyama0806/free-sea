#pragma once
#include "BulletBase.h"

class ReflectionBullet : public BulletBase
{
private:
	static constexpr int MaxHealth = 5;			//反射できる回数(体力)
	static constexpr float AddForce = 550.0f;	//投げる力

public:
	//コンストラクタ
	ReflectionBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		BulletBase(position, forward, stage, MaxHealth, AddForce)
	{
	}
};