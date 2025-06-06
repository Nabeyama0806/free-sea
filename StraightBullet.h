#pragma once
#include "Bullet.h"

class StraightBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//���˂ł����(�̗�)
	static constexpr int Powar = 20;
	static constexpr float AddForce = 1050.0f;	//�������

public:
	//�R���X�g���N�^
	StraightBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(position, forward, stage, MaxHealth, Powar, AddForce)
	{
	}
};