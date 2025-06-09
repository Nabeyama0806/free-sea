#pragma once
#include "ModelActor.h"
#include "CharacterBase.h"
#include "DxLib.h"

class Stage;

class Bullet : public ModelActor
{
private:
	static constexpr float Scale = 25.0f;		//�傫���̒���
	static constexpr float EraseTime = 2.5f;	//��������

	Stage* m_stage;
	Vector3 m_forward;		//���g�̐��ʃx�N�g��

	int m_health;			//���˂ł����
	int m_power;			//�U����
	float m_addForce;		//�������
	float m_elapsedTime;	//��������Ă���̐�������

	virtual void Update() override;		//�X�V

public:
	//�R���X�g���N�^
	Bullet(
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		int maxHelath,
		int power,
		float addForce,
		float Size = 30
	);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other) 
	{
		if (other->GetName() == "Player")
		{
			//�����̐e�Ȃ�_���[�W��^���Ȃ�
			if (GetParent() == other) return;
			
			//���v���C���[�ƏՓ˂�����_���[�W��^����
			dynamic_cast<CharacterBase*>(const_cast<ModelActor*>(other))->Damage(m_power);
			Destroy();
		}
	}
};