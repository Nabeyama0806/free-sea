#pragma once
#include "CharacterBase.h"

class GreenBird : public CharacterBase
{
private:
	static constexpr int Health = 170;
	static constexpr int BulletAmount = 2;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.0f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.3f;		//�e�Ԃ̔��ˊԊu

	void BulletShot();		//����
	bool BulletInstance();	//�e�̐���

protected:
	virtual void Update() override;			//�X�V

public:
	//�R���X�g���N�^
	GreenBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};