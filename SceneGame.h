#pragma once
#include"SceneBase.h"
#include"Character.h"
#include "InputSystem.h"
#include "Vector3.h"
#include <list>
#include <vector>

//�N���X�̑O���錾
class Node;
class ModelActor;
class Sprite;
class Camera;
class Transform;
class Stage;

//�Q�[���V�[��
class SceneGame : public SceneBase
{	
private:
	static constexpr float ResultTransitionTime = 2.0f;		//�v���C���[������ł��烊�U���g��ʂɑJ�ڂ���܂ł̎���

	//���f���̎��O�ǂݍ���
	const std::list<const char*> ModelPreload =
	{
		"Man/Man.mv1",
		"Man/Man4.mv1",
		"Man/Man3.mv1",
		"Man/Man2.mv1",
	};


	//�L�����N�^�[�A�C�R���̃t�@�C���p�X
	const char* CharacterIconFilePath[InputSystem::MaxPadAmount] =
	{
		"Resource/Texture/status_icon_blue.png",
		"Resource/Texture/status_icon_green.png",
		"Resource/Texture/status_icon_red.png",
		"Resource/Texture/status_icon_pink.png",
	}; 

	//�L�����N�^�[�A�C�R���̖��O
	const char* CharacterIconName[InputSystem::MaxPadAmount] =
	{
		"blue_bird_icon",
		"green_bird_icon",
		"red_bird_icon",
		"pink_bird_icon",
	};

	//�L�����N�^�[�A�C�R���̈ʒu
	const Vector2 CharacterIconPosition[InputSystem::MaxPadAmount] =
	{
		Vector2(200, 150),
		Vector2(200, 300),
		Vector2(200, 450),
		Vector2(200, 600),
	};

	const Vector3 PlayerPosition[InputSystem::MaxPadAmount] =
	{
		Vector3(-620, 0, 0),
		Vector3(620, 0, 0),
		Vector3(0, 0, 450),
		Vector3(0, 0, -450),
	};

	Node* m_rootNode;
	Character* m_characters[InputSystem::MaxPadAmount];
	Camera* m_mainCamera;
	Stage* m_stage;
	Sprite* m_sprite;	//�L�����N�^�[�A�C�R���̕\���p
	Transform m_transform;

	Vector3 cameraPos = Vector3(0, 0, -700);
	std::vector<int> m_playerBullets;

	float m_resultTransitionTime;
	int m_padAmount;	
	int m_bgm;

	//�Ō�̃v���C���[������
	void IsLastCharacter() const;

public:
	//�R���X�g���N�^
	SceneGame(std::vector<int>& playerBullets, int padAmount) :
		m_padAmount(padAmount),
		m_rootNode(nullptr),
		m_stage(nullptr),
		m_mainCamera(nullptr),
		m_sprite(nullptr),
		m_characters{nullptr},
		m_resultTransitionTime(ResultTransitionTime),
		m_playerBullets(playerBullets),
		m_bgm(0)
	{
	}

	virtual void Preload() override;		//���O�ǂݍ���
	virtual void Initialize() override;		//������
	virtual void Finalize() override;		//�I��
	virtual void Update() override;			//�X�V
	virtual void Draw() override;			//�`��
};