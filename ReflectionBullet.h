#pragma once
#include "Bullet.h"

class ReflectionBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 5;			//���˂ł����(�̗�)
	static constexpr int Powar = 10;
	static constexpr float AddForce = 450.0f;	//�������
	static constexpr float Size = 25;

public:
	//�R���X�g���N�^
	ReflectionBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(position, forward, stage, MaxHealth, Powar, AddForce, Size)
	{
	}
};