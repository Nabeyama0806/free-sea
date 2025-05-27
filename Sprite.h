#pragma once
#include "Vector2.h"
#include "Transform.h"
#include "SpriteAnimation.h"
#include <map>	//�A�z�z��

class Sprite
{
private:
	std::map<const char*, SpriteAnimation> m_spriteAnimationList;//<�A�j���[�V�������F�A�j���[�V�����f�[�^>�̘A�z�z��
	const SpriteAnimation* m_runningAnime;	//�Đ����A�j���[�V�������X�g�ւ̃|�C���^
	float m_elapsedTime;					//�o�ߎ���(�b�j

public:
	Vector2 gridSize;	//�A�j���[�V�����̂̕��A����
	bool flipX;			//���E���]
	bool flipY;			//�㉺���]

	//�R���X�g���N�^
	Sprite() :
		m_runningAnime(nullptr),
		m_elapsedTime(0),
		flipX(false),
		flipY(false) {
	}

	//�f�X�g���N�^
	virtual ~Sprite();

	//�摜�̓ǂݍ���
	void Load();

	//�摜�̊J��
	void Release();

	//�X�V
	void Update();

	//�`��
	void Draw(const Transform& transform);

	//�A�j���[�V�����̓o�^
	void Register(const char* textureName);
	void Register(const char* animeName, const SpriteAnimation& spriteAnimation);

	//�A�j���[�V�����̍Đ�
	void Play(const char* animeName);

	//�A�j���[�V����1�R�}�̕`�掞�Ԃ��擾
	float GetFrameTime()
	{
		return m_runningAnime ? 1.0f / m_runningAnime->sampleRate : 0.0f;
	}

	//�A�j���[�V�����̑����Ԃ��擾
	float GetTotalFrameTime()
	{
		return m_runningAnime ? GetFrameTime() * m_runningAnime->gridAmount : 0.0f;
	}

	//�A�j���[�V�������I���������ǂ���
	bool IsFinishAnime()
	{
		return m_runningAnime ? m_elapsedTime >= GetTotalFrameTime() : true;
	}
};
