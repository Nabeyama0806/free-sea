#pragma once
#include "ActorBase.h"
#include "Screen.h"
#include <string>

class Sprite;

class SpriteActor : public ActorBase
{
protected: 
	Sprite* m_sprite;		//2D�摜

	virtual void Load() override;	//���\�[�X�̓ǂݍ���
	virtual void Release() override;	//���\�[�X�̊J��
	virtual void Draw() override;	//���\�[�X�̊J��

public:
	//�R���X�g���N�^
	SpriteActor(const char* name,
		const char* textureName = nullptr,
		const Vector3& position = Vector2()
	);

	//�q�m�[�h���܂ލX�V
	virtual void TreeUpdate() override;
};