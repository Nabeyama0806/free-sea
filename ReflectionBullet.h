#pragma once
#include "Bullet.h"
#include "Stage.h"

class ReflectionBullet : public Bullet
{
private:
	static constexpr int Power = 20;			//�U����
	static constexpr float AddForce = 500.0f;	//�������

public:
	//�R���X�g���N�^
	ReflectionBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage)
	{
		//�e�̃X�e�[�^�X��ݒ�
		m_power = Power;
		m_addForce = AddForce;
	}

	static constexpr int BulletAmount = 5;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.4f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.25f;	//�e�Ԃ̔��ˊԊu
};