#pragma once
#include "ModelActor.h"
#include "Bullet.h"
#include "Vector3.h"
#include "Vector2.h"
 
class SpriteActor;
class Camera;
class Stage;

class CharacterBase : public ModelActor
{
private:
	static constexpr int MaxPlayerAmount = 4;

	static constexpr int MaxHealth = 160;			//�̗�
	static constexpr float Scale = 3.0f;			//���g�̃T�C�Y
	static constexpr float Speed = 1.2f * Scale;	//���g�̃T�C�Y�ɍ������ړ����x
	static constexpr float Radius = 20.0f;			//�Փ˔���̔��a
	static constexpr float FlashTime = 0.8f;		//�_�Ŏ���

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
		"Man/Walking.mv1"	//�ړ�
	};

	const Vector2 HealthDrawPos[MaxPlayerAmount] =
	{
		Vector2(250, 140),
		Vector2(250, 290),
		Vector2(250, 440),
		Vector2(250, 590),
	};
 
protected:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);
	static constexpr int HealthSlideHeight = 40;

	const char* BulletFilePath;

	SpriteActor* m_spriteActor;
	Camera* m_camera;
	Stage* m_stage;				
	Vector2 m_shotRotate;		//�ˏo�����̉�]
	Vector2 m_inputValue;		//���͒l	
	Bullet::Type m_bulletType;	//�e�̎��

	//���g�Ɋւ���ϐ�
	int m_maxHealth;			//�ő�̗�
	int m_health;				//�̗�
	int m_playerIndex;			//���g�̃v���C���[�ԍ�
	float m_flashTime;			//�c��̓_�Ŏ���
	bool m_isGrounded;			//���Ƃ̐ڐG����

	//�e�̐����ɕK�v�ȕϐ�
	int m_bulletInstanceAmount;	//�������ꂽ�e�̐�
	float m_shotElapsedTime;	//���ˊԊu�̌o�ߎ���
	float m_bulletElapsedTime;	//�e�Ԃ̌o�ߎ���
	int	m_maxBulletAmount;		//���Ŕ��˂����e�̐�
	float m_shotCoolTime;		//���ˊԊu
	float m_bulletFiringRate;	//�e�Ԃ̔��ˊԊu
	bool m_isShot;				//���˒�

	virtual void Update() override;	//�X�V
	virtual void Draw() override;	//�`��

	virtual void BulletShot();		//�e�̔���
	virtual bool CreateBullet();	//�e�̐���

public:
	//�R���X�g���N�^
	CharacterBase(
		const char* modelFilepath,
		const char* bulletFilePath,
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		Bullet::Type bulletType,
		int playerIndex
	);

	//��e
	void Damage(int damage);

	//�ˏo�����̎擾
	Vector3 GetShotForward()
	{
		float length = 80.0f;	//�ˏo�����̒���
		Vector3 tmp = Vector3(m_shotRotate.x, 0, m_shotRotate.y);
		if (!tmp.IsZero()) m_shotRotate.Normalize();
		else
		{
			Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
			m_shotRotate = forward;
			tmp = forward;
		}
		return tmp;
	}

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other) {};
};