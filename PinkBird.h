#pragma once
#include "CharacterBase.h"

class PinkBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 2;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.0f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.3f;		//�e�Ԃ̔��ˊԊu

	void BulletShot();		//����
	bool BulletInstance();	//�e�̐���

protected:
	virtual void Update() override;			//�X�V
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	PinkBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};