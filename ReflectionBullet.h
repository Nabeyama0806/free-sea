#pragma once
#include "BulletBase.h"

class ReflectionBullet : public BulletBase
{
private:
	static constexpr int MaxHealth = 5;			//���˂ł����(�̗�)
	static constexpr float AddForce = 550.0f;	//�������

public:
	//�R���X�g���N�^
	ReflectionBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		BulletBase(position, forward, stage, MaxHealth, AddForce)
	{
	}
};