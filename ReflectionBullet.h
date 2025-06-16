#pragma once
#include "Bullet.h"
#include "Stage.h"

class ReflectionBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 5;			//���˂ł����(�̗�)
	static constexpr int Power = 13;
	static constexpr float AddForce = 500.0f;	//�������
	static constexpr float Size = 25;

public:
	//�R���X�g���N�^
	ReflectionBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(position, forward, stage, MaxHealth, Power, AddForce, Size)
	{
	}
};