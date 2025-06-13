#pragma once
#include "SceneBase.h"
#include "CharacterBase.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Node.h"
#include "Transform.h"
#include <vector>

class Node;

//�^�C�g���V�[��
class SceneTitle : public SceneBase
{
private:
	enum class Phase
	{
		Home,		//�n�܂�
		Select,		//�L�����I��
		GameStart,	//�Q�[���J�n

		Length
	};
	Phase m_phase;

private:
	const char* CharaTextureName[static_cast<int>(CharacterBase::Type::Length)] =
	{
		"Blue",
		"Green",
	};

	const SpriteAnimation FilePath[static_cast<int>(CharacterBase::Type::Length)] =
	{
		SpriteAnimation("Resource/Texture/bird_blue.png", 1, 1, false),
		SpriteAnimation("Resource/Texture/bird_green.png", 1, 1, false),
	};

	std::vector<int> m_select;	//�I������Ă���L�����N�^�[

	Node* m_rootNode;
	Transform m_transform;
	Sprite* m_sprite;
	int m_padAmount;

public:
	//�R���X�g���N�^
	SceneTitle() :
		m_phase(Phase::Home),
		m_rootNode(nullptr),
		m_sprite(nullptr),
		m_select(0) ,
		m_padAmount(0)
	{
	}

	virtual void Initialize() override;				//������
	virtual void Finalize() override;				//�I��
	virtual SceneBase* Update() override;			//�X�V
	virtual void Draw() override;					//�`��
};