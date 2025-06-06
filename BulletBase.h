#pragma once
#include "ModelActor.h"

class Stage;

class BulletBase : public ModelActor
{
private:
	static constexpr float Scale = 25.0f;		//�傫���̒���
	static constexpr float EraseTime = 3.0f;	//��������

	Stage* m_stage;
	Vector3 m_forward;		//���g�̐��ʃx�N�g��

	int m_maxHealth;		//���˂ł����(�̗�)
	int m_health;			//���݂̗̑�
	float m_addForce;		//�������
	float m_elapsedTime;	//��������Ă���̐�������

	virtual void Update() override;		//�X�V

public:
	//�R���X�g���N�^
	BulletBase(
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		int maxHelath,
		float addForce
	);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other) {};
};