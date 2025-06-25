#pragma once
#include "Bullet.h"
#include "DxLib.h"

class StraightBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//���˂ł����(�̗�)
	static constexpr int Power = 50;			//�U����
	static constexpr float AddForce = 950.0f;	//�������

public:
	//�R���X�g���N�^
	StraightBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage)
	{
		//�e�̃X�e�[�^�X��ݒ�
		m_health = MaxHealth;
		m_power = Power;
		m_addForce = AddForce;
	}

	static constexpr int BulletAmount = 2;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.0f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.3f;		//�e�Ԃ̔��ˊԊu
};