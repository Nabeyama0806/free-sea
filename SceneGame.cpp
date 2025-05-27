#include "SceneGame.h"
#include "SceneResult.h"
#include "Screen.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Fade.h"
#include "Camera.h"
#include "Player.h"
#include "ImageLoader.h"
#include "ModelLoader.h"
#include "DxLib.h"

//������
void SceneGame::Initialize()
{
	//���[�g
	m_rootNode = new Node();

	//���C���J����
	m_mainCamera = new Camera();
	m_rootNode->AddChild(m_mainCamera);

	//�w�i
	m_rootNode->AddChild(new ModelActor("Ground", "Environment/Environment.mv1"));

	//�A�N�^�[���C���[
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//UI���C���[
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//�v���C���[
	m_player = new Player(m_mainCamera);
	m_rootNode->AddChild(m_player);
	m_mainCamera->SetLookAt(m_player);

	//BGM

}

//�I��
void SceneGame::Finalize()
{
	//�m�[�h�̍폜
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;

	//BGM
	DeleteSoundMem(m_bgm);
}

//�X�V
SceneBase* SceneGame::Update()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();
	return this;
}

//�`��
void SceneGame::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();
}