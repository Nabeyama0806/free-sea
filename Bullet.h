#pragma once
#include "ModelActor.h"
#include "DxLib.h"

class Stage;

class Bullet : public ModelActor
{
public:
	enum class Type
	{
		Reflection,		//���˒e
		Straight,		//���i�e
		Diffusion,		//�g�U�e

		Length,		
	};

	int m_health;				//���˂ł����
	int m_power;				//�U����
	float m_addForce;			//�������
	float m_elapsedTime;		//��������Ă���̐�������
	float m_size;				//�傫���̒���
	float m_eraseTime;			//��������(�b)

private:
	static constexpr int MaxHealth = 3;
	static constexpr int Power = 15;
	static constexpr float AddForce = 500.0f;
	static constexpr float Size = 2.0f;	
	static constexpr float EraseTime = 2.0f;	

	Stage* m_stage;
	Vector3 m_forward;		//���g�̐��ʃx�N�g��

	virtual void Update() override;		//�X�V

public:
	//�R���X�g���N�^
	Bullet(
		const char* filePath,
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		const float size = Size
	);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other);
};