#pragma once
#include "ModelActor.h"
#include "Vector3.h"

class Camera;
class Stage;

class PlayerBase : public ModelActor
{
public:
	enum class Bullet
	{
		Straight,
		Reflect,
	};

private:
	enum class Anime
	{
		Idle,
		Run,

		Length,
	};

	//�A�j���[�V�����z��
	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//�ҋ@
		"Man/Sprint.mv1"	//�ړ�
	};

private:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);
	static constexpr float Scale = 3.0f;			//���g�̃T�C�Y
	static constexpr float Speed = 1.2f * Scale;	//���g�̃T�C�Y�ɍ������ړ����x
	static constexpr float Radius = 20.0f;			//�Փ˔���̔��a

	Camera* m_camera;
	Stage* m_stage;
	Bullet m_bullet;
	int m_playerIndex;			//���g�̃v���C���[�ԍ�
	bool m_isGrounded;			//���Ƃ̐ڐG����
	bool m_isShot;				//���˒�

	//�e
	int	m_maxBulletAmount;		//���Ŕ��˂����e�̐�
	float m_shotCoolTime;		//���ˊԊu
	float m_bulletFiringRate;	//�e�Ԃ̔��ˊԊu

	int m_bulletInstanceAmount;	//�������ꂽ�e�̐�
	float m_shotElapsedTime;	//���ˊԊu�̌o�ߎ���
	float m_bulletElapsedTime;	//�e�Ԃ̌o�ߎ���

	void Move(Anime& anime);		//�ړ�
	void BulletShot();				//����
	bool BulletInstance();			//�e�̐���

protected:
	virtual void Update() override;	//�X�V
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	PlayerBase(
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		Bullet bullet,
		int playerIndex,
		int maxBulletAmount,
		float shotCoolTime,
		float bulletFiringRate
	);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other) {};
};