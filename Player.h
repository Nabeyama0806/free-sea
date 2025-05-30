#pragma once
#include "ModelActor.h"
#include "Model.h"
#include "Vector3.h"
#include "Camera.h"
#include <vector>

class Camera;

class Player : public ModelActor
{
private:
	enum class Anime
	{
		Idle,
		Run,

		Length,
	};

	static constexpr Vector3 SpawnPos = Vector3(0, 0, 0);		//�J�n���̍��W
	static constexpr Vector3 Scale = Vector3(3.0f, 3.0f, 3.0f);	//���g�̃T�C�Y
	static constexpr Vector3 BulletPosOffset = Vector3(0, 50, 0);
	static constexpr float Speed = 1.2f * Scale.y;	//���g�̃T�C�Y�ɍ������ړ����x
	static constexpr float Radius = 20.0f;			//�Փ˔���̔��a

	//�e
	static constexpr int BulletAmount = 3;				//���Ŕ��˂����e�̐�
	static constexpr float ShotCoolTime = 1.6f;			//���ˊԊu
	static constexpr float BulletFiringRate = 0.25f;	//�e�Ԃ̔��ˊԊu

	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//�ҋ@
		"Man/Sprint.mv1"	//�ړ�
	};

	Camera* m_camera;
	Vector3 m_prevPos;
	int m_mapModelHandle;		//�}�b�v�̎��ʔԍ�
	int m_bulletInstanceAmount;	//�������ꂽ�e�̐�
	float m_shotElapsedTime;	//���ˊԊu�̌o�ߎ���
	float m_bulletElapsedTime;	//�e�Ԃ̌o�ߎ���
	bool m_isGrounded;			//���Ƃ̐ڐG����
	bool m_isShot;				//���˒�

	void Move(Anime& anime);		//�ړ�
	void BulletShot();				//����
	bool BulletInstance();			//�e�̐���

protected:
	virtual void Update() override;	//�X�V
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	Player(Camera* camera, int mapModelHandle);
};