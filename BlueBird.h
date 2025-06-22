#pragma once
#include "CharacterBase.h"
#include "Bullet.h"

class BlueBird : public CharacterBase
{
private:
	static constexpr int BulletAmount = 2;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 0.8f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.2f;		//�e�Ԃ̔��ˊԊu

	const char* BulletFilePath = "Resource/Model/Bullet.mv1";	//�e�̃��f���t�@�C���p�X

public:
	//�R���X�g���N�^
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType) :
		CharacterBase("Man/Man.mv1", BulletFilePath, camera, stage, position, bulletType)
	{
		//�e
		m_maxBulletAmount = BulletAmount;
		m_shotCoolTime = ShotCoolTime;
		m_bulletFiringRate = BulletFiringRate;
	}
};