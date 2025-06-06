#pragma once
#include "Bullet.h"

class ReflectionBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 5;			//反射できる回数(体力)
	static constexpr int Powar = 10;
	static constexpr float AddForce = 450.0f;	//投げる力
	static constexpr float Size = 25;

public:
	//コンストラクタ
	ReflectionBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(position, forward, stage, MaxHealth, Powar, AddForce, Size)
	{
	}
};