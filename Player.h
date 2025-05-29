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
	static constexpr Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);	//���g�̃T�C�Y
	static constexpr float Speed = 7.5f * Scale.y;	//���g�̃T�C�Y�ɍ������ړ����x
	static constexpr float Radius = 40.0f;			//�Փ˔���̔��a
	static constexpr int AnimeAmount = 2;			//�A�j���[�V�����̑���

	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//�ҋ@
		"Man/Sprint.mv1"	//�_�b�V��
	};

	Camera* m_camera;
	Vector3 m_prevPos;
	int m_mapModelHandle;	//�}�b�v�̎��ʔԍ�
	bool m_isGrounded;		//���Ƃ̐ڐG����

protected:
	virtual void Update() override;	//�X�V
	virtual void Draw() override;

public:
	//�R���X�g���N�^
	Player(Camera* camera, int mapModelHandle);
};