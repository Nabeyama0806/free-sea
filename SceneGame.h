#pragma once
#include"SceneBase.h"
#include"CharacterBase.h"
#include "ModelLoader.h"
#include "Vector3.h"
#include <list>
#include <vector>

//�N���X�̑O���錾
class Node;
class ModelActor;
class Camera;
class Stage;

//�Q�[���V�[��
class SceneGame : public SceneBase
{	
private:
	static constexpr int MaxControllerNum = 4;
	static constexpr float ResultTransitionTime = 2.0f;		//�v���C���[������ł��烊�U���g��ʂɑJ�ڂ���܂ł̎���

	const std::list<const char*> ModelPreload =
	{
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_green.mv1",
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_pink.mv1",
	};

	const Vector3 PlayerPosition[MaxControllerNum] =
	{
		Vector3(-620, 0, 0),
		Vector3(620, 0, 0),
		Vector3(0, 0, 450),
		Vector3(0, 0, -450),
	};

	Node* m_rootNode;
	CharacterBase* m_characters[MaxControllerNum];
	Camera* m_mainCamera;
	Stage* m_stage;

	Vector3 cameraPos = Vector3(0, 0, -700);
	std::vector<int> m_playerBullets;

	float m_resultTransitionTime;
	int m_bgm;

public:
	//�R���X�g���N�^
	SceneGame(std::vector<int>& playerBullets) :
		m_rootNode(nullptr),
		m_stage(nullptr),
		m_mainCamera(nullptr),
		m_characters{nullptr},
		m_resultTransitionTime(ResultTransitionTime),
		m_playerBullets(playerBullets),
		m_bgm(0)
	{
		//���f���̃v�����[�h
		/*for (const char* modelPath : ModelPreload)
		{
			ModelLoader::GetInstance()->Load(modelPath);
		}*/
	}

	virtual void Initialize() override;		//������
	virtual void Finalize() override;		//�I��
	virtual SceneBase* Update() override;	//�X�V
	virtual void Draw() override;			//�`��
};