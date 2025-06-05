#pragma once
#include"SceneBase.h"
#include "Vector3.h"
#include <list>

//�N���X�̑O���錾
class Node;
class ModelActor;
class Camera;
class Stage;
class Player;

//	�Q�[���V�[��
class SceneGame : public SceneBase
{
private:
	const std::list<const char*> ImagePreload =
	{
		//"title.png"
	};

	static constexpr float ResultTransitionTime = 2.0f;	//�v���C���[������ł��烊�U���g��ʂɑJ�ڂ���܂ł̎���
	Node* m_rootNode;		
	Player* m_player1;	
	Player* m_player2;	
	Camera* m_mainCamera;	
	Stage* m_stage;			

	Vector3 cameraPos = Vector3(0, 0, -700);

	float m_resultTransitionTime;
	int m_playerIndex;
	int m_bgm;

public:
	//�R���X�g���N�^
	SceneGame() :
		m_rootNode(nullptr), 
		m_stage(nullptr),
		m_player1(nullptr),
		m_player2(nullptr),
		m_mainCamera(nullptr),
		m_resultTransitionTime(ResultTransitionTime),
		m_playerIndex(0),
		m_bgm(0){}

	virtual void Initialize() override;		//������
	virtual void Finalize() override;		//�I��
	virtual SceneBase* Update() override;	//�X�V
	virtual void Draw() override;			//�`��
};