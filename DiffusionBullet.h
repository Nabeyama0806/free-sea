#pragma once
#pragma once
#include "Bullet.h"
#include "Stage.h"

class DiffusionBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//���˂ł����(�̗�)
	static constexpr int Power = 15;			//�U����
	static constexpr float AddForce = 550.0f;	//�������
	static constexpr float Size = 20.0f;		//�傫���̒���
	static constexpr float EraseTime = 0.8f;	//��������(�b)

public:
	//�R���X�g���N�^
	DiffusionBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage, Size)
	{
		//�e�̃X�e�[�^�X��ݒ�
		m_health = MaxHealth;
		m_power = Power;
		m_addForce = AddForce;
		m_eraseTime = EraseTime;
	}

	static constexpr int BulletAmount = 2;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 0.8f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.2f;		//�e�Ԃ̔��ˊԊu

	static constexpr int DiffusionBulletAmount = 3;		//�g�U�e�̐�
	static constexpr float AngleRate = 6.0f;			//�g�U�e�̊p�x
};