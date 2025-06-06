#pragma once
#include "PlayerBase.h"

class Player : public PlayerBase
{
private:
	//�e
	static constexpr int BulletAmount = 3;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.4f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.27f;	//�e�Ԃ̔��ˊԊu

public:
	//�R���X�g���N�^
	Player(Camera* camera, Stage* stage, const Vector3& position, PlayerBase::Bullet bullet, int playerIndex);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other);
};