#pragma once
#include "ModelActor.h"
#include "Stage.h"
#include <string>

class BulletStatus;

class Bullet : public ModelActor
{
private:
	static constexpr float Size = 0.1f; //�e�̑傫��

	Stage* m_stage;	
	Vector3 m_forward;	
	float m_elapsedTime;

	//�e�̃X�e�[�^�X
	BulletStatus* m_bulletStatus;

	int m_reflectAmount;		//���ˉ\��
	float m_addForce;			//�������
	int m_power;				//�U����
	float m_aliveTime;			//��������(�b)
	float m_size;				//�傫��

protected:
	virtual void Update() override;		//�X�V

public:
	// �R���X�g���N�^
	Bullet(
		const char* filePath,
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		int bulletIndex
	);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other);
};