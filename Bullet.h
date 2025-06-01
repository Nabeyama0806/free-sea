#pragma once
#include "ModelActor.h"

class Player;

class Bullet : public ModelActor
{
public:
	static constexpr int MaxHealth = 3;			//���˂ł����(�̗�)
	static constexpr float Scale = 20.0f;		//�傫���̒���

private:
	static constexpr float AddForce = 550.0f;	//�������
	static constexpr float EraseTime = 3.0f;	//��������

	Player* m_player;		//�v���C���[
	Vector3 m_forward;		//���g�̐��ʃx�N�g��
	int m_health;			//���݂̗̑�
	float m_elapsedTime;	//��������Ă���̐�������

	virtual void Update() override;			//�X�V

public:
	//�R���X�g���N�^
	Bullet(const Vector3& position, const Vector3& forward, Player* player);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other);
	virtual void OnHitPolygon(const ColliderResult* result);
};