#pragma once
#include "CharacterBase.h"

class BlueBird : public CharacterBase
{
private:
	//�e
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 5;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.7f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.24f;	//�e�Ԃ̔��ˊԊu
	void BulletShot();		//����
	bool BulletInstance();	//�e�̐���

protected:
	virtual void Update() override;			//�X�V

public:
	//�R���X�g���N�^
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};