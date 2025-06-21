#pragma once
#include "CharacterBase.h"

class BlueBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 5;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.7f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.24f;	//�e�Ԃ̔��ˊԊu

public:
	//�R���X�g���N�^
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex) :
		CharacterBase("Man/Man.mv1", camera, stage, position, Health, playerIndex)
	{
		//�e
		m_maxBulletAmount = BulletAmount;
		m_shotCoolTime = ShotCoolTime;
		m_bulletFiringRate = BulletFiringRate;
	}
};