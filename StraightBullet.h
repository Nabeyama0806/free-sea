#pragma once
#include "BulletBase.h"

class StraightBullet : public BulletBase
{
private:
	static constexpr int MaxHealth = 1;			//���˂ł����(�̗�)
	static constexpr float AddForce = 1200.0f;	//�������

public:
	//�R���X�g���N�^
	StraightBullet(const Vector3& position, const Vector3& forward, Stage* stage) :
		BulletBase(position, forward, stage, MaxHealth, AddForce)
	{
	}
};