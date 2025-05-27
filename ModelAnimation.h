#pragma once
#include "Dxlib.h"
#include "ModelActor.h"
#include <vector>

class Transform;

class ModelAnimation
{
private:
	static constexpr int FPS = 60;					//�t���[�����[�g
	static constexpr float BlendDuration = 0.3f;	//�A�j���[�V�����̕K�v����

	const char* m_animeFileName;
	int m_modelHandle;			//�A�j���[�V�����̃A�^�b�`��
	int m_animeHandle;			//�A�j���[�V�������f��
	int m_attachIndex;			//�A�^�b�`����A�j���[�V�����̗v�f�ԍ�

	float m_animeTime;			//�A�j���̍Đ�����
	float m_animeTotalTime;		//�A�j���̑��Đ�����

	float m_blendStart;	//�A�j���[�V�����J�n�̉e���x
	float m_blendEnd;	//�A�j���[�V�����I���̉e���x
	float m_blendTime;	//�A�j���[�V�����J�ڊJ�n����̌o�ߎ���

	bool m_isFarst;		//�擪�̃A�j�����ǂ���
	
public:
	//�f�X�g���N�^
	virtual ~ModelAnimation();
	
	//�R���X�g���N�^
	ModelAnimation(const char* animeFileName, const bool isFast);

	//���\�[�X�̓ǂݍ���
	void Load(const int modelHandle);

	//���\�[�X�̉��
	void Release();

	//�X�V
	void Update();

	//�A�j���[�V�����J�n
	void FadeIn()
	{
		m_blendTime = 0.0f;
		m_blendStart = 0.0f;
		m_blendEnd = 1.0f;
	}

	//�A�j���[�V�����I��
	void FadeOut()
	{
		m_blendTime = 0.0f;
		m_blendStart = 1.0f;
		m_blendEnd = 0.0f;
	}

	bool IsFade() { return m_blendTime >= 0; }
};