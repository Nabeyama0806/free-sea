#pragma once
#include "CharacterBase.h"

class RedBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 3;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.2f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.3f;		//�e�Ԃ̔��ˊԊu

public:
	//�R���X�g���N�^
	RedBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType) :
		CharacterBase("Man/Man3.mv1", "Resource/Model/bullet_red.mv1", camera, stage, position, bulletType)
	{
		//�e
		m_maxBulletAmount = BulletAmount;
		m_shotCoolTime = ShotCoolTime;
		m_bulletFiringRate = BulletFiringRate;
	}
};