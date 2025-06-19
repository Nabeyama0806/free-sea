#pragma once
#include "CharacterBase.h"

class RedBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 1;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 0.7f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.7f;	//�e�Ԃ̔��ˊԊu

	void BulletShot();		//����
	bool BulletInstance();	//�e�̐���

protected:
	virtual void Update() override;			//�X�V

public:
	//�R���X�g���N�^
	RedBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};