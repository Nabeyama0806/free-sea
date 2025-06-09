#pragma once
#include "Bullet.h"
#include "DxLib.h"

class StraightBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//反射できる回数(体力)
	static constexpr int Power = 30;
	static constexpr float AddForce = 950.0f;	//投げる力

public:
	//コンストラクタ
	StraightBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(position, forward, stage, MaxHealth, Power, AddForce)
	{
	}
};