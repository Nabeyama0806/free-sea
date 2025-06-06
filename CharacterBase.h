#pragma once
#include "ModelActor.h"
#include "Vector3.h"

class Camera;
class Stage;

class CharacterBase : public ModelActor
{
private:
	static constexpr float Scale = 3.0f;			//���g�̃T�C�Y
	static constexpr float Speed = 1.2f * Scale;	//���g�̃T�C�Y�ɍ������ړ����x
	static constexpr float Radius = 45.0f;			//�Փ˔���̔��a
	static constexpr float InvincibleTime = 0.8f;	//���G����

	//�A�j���[�V�����p�^�[��
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

protected:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);

	const char* m_modelFilePath;
	Camera* m_camera;
	Stage* m_stage;
	int m_playerIndex;			//���g�̃v���C���[�ԍ�
	float m_invincibleTime;		//�c��̖��G����
	bool m_isGrounded;			//���Ƃ̐ڐG����
	bool m_isShot;				//���˒�

	int m_bulletInstanceAmount;	//�������ꂽ�e�̐�
	float m_shotElapsedTime;	//���ˊԊu�̌o�ߎ���
	float m_bulletElapsedTime;	//�e�Ԃ̌o�ߎ���

	int m_health;				//�̗�
	int	m_maxBulletAmount;		//���Ŕ��˂����e�̐�
	float m_shotCoolTime;		//���ˊԊu
	float m_bulletFiringRate;	//�e�Ԃ̔��ˊԊu

	virtual void Update() override;	//�X�V
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	CharacterBase(
		const char* modelFilepath,
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		int health,
		int playerIndex
	);

	//��e
	void Damage(int damage);

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other) {};
};