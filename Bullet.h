#pragma once
#include "ModelActor.h"

class Player;

class Bullet : public ModelActor
{
public:
	static constexpr Vector3 Scale = Vector3(15, 15, 15);		//�傫���̒���

private:
	static constexpr float AddForce = 700;		//�������
	static constexpr float EraseTime = 3.0f;	//��������

	Player* m_player;
	Vector3 m_forward;
	float m_elapsedTime;	//��������Ă���̐�������

	virtual void Update() override;		//�X�V
	Vector3 Shot(Vector3& position) const;

public:
	//�R���X�g���N�^
	Bullet(const Vector3& position, const Vector3& forward, Player* player);
};