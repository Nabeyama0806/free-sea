#pragma once
#include "SceneBase.h"
#include "Transform.h"
#include "Node.h"
#include "InputSystem.h"
#include "ModelLoader.h"
#include "Sprite.h"
#include <vector>

class Node;
class SpriteActor;

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
	const std::list<const char*> ModelPreload =
	{
		"Resource/Model/bullet_blue.mv1",
		"Resource/Model/bullet_green.mv1",
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_pink.mv1",
	};

	//�e�̎��
	/*const char* CharacterImage[static_cast<int>(Bullet::Type::Length)] =
	{
		"Resource/Texture/reflection.png",
		"Resource/Texture/straight.png",
		"Resource/Texture/diffusion.png",
		"Resource/Texture/laser.png",
	};*/


	const Vector2 DrawPosOffset[InputSystem::MaxPadAmount] =
	{
		Vector2(-430.0f, -110.0f),
		Vector2(630.0f, -110.0f),
		Vector2(-430.0f, 325.0f),
		Vector2(630.0f, 325.0f),
	};

	std::vector<int> m_select;	//�I������Ă���e

	Node* m_rootNode;
	Transform m_transform;
	Sprite* m_sprites[InputSystem::MaxPadAmount];
	int m_padAmount;
	int m_bgm;

public:
	//�R���X�g���N�^
	SceneTitle() :
		m_phase(Phase::Home),
		m_rootNode(nullptr),
		m_sprites{nullptr},
		m_select(0) ,
		m_padAmount(0),
		m_bgm(0)
	{
		//���f���̃v�����[�h
		for (const char* modelPath : ModelPreload)
		{
			ModelLoader::GetInstance()->Load(modelPath);
		}
	}

	virtual void Initialize() override;				//������
	virtual void Finalize() override;				//�I��
	virtual SceneBase* Update() override;			//�X�V
	virtual void Draw() override;					//�`��
};