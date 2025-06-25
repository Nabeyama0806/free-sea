#pragma once
#pragma once
#include "Bullet.h"
#include "Stage.h"

class LaserBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//���˂ł����(�̗�)
	static constexpr int Power = 10;			//�U����
	static constexpr float AddForce = 750.0f;	//�������
	static constexpr float EraseTime = 10.0f;	//��������(�b)

public:
	//�R���X�g���N�^
	LaserBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage)
	{
		//�e�̃X�e�[�^�X��ݒ�
		m_health = MaxHealth;
		m_power = Power;
		m_addForce = AddForce;
		m_eraseTime = EraseTime;
	}

	static constexpr int BulletAmount = 1;			//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 0.1f;		//���ˊԊu
	static constexpr float BulletFiringRate = 0.1f;	//�e�Ԃ̔��ˊԊu
};