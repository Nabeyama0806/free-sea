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
	static constexpr Vector3 SpawnOffset = Vector3(0, 0, 400);	//�J�n���̍��W
	static constexpr Vector3 Scale = Vector3(1.5f, 1.5f, 1.5f);	//���g�̃T�C�Y
	static constexpr float Speed = 7.5f * Scale.y;	//���g�̃T�C�Y�ɍ������ړ����x
	static constexpr float DashSpeed = 1.4f;		//�_�b�V�����̑��x�{��
	static constexpr int AnimeAmount = 2;			//�A�j���[�V�����̑���

	const char* AnimeFileName[AnimeAmount] =
	{
		"Man/Idle.mv1",		//�ҋ@
		"Man/Sprint.mv1"	//�_�b�V��
	};

	Camera* m_camera;
protected:
	virtual void Update() override;	//�X�V
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	Player(Camera* camera);
};