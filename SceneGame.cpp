#include "SceneGame.h"
#include "SceneResult.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Camera.h"
#include "Player.h"
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
	m_map = new ModelActor("Ground", "Environment/Ground.mv1");
	MV1SetupCollInfo(m_map->GetModelHandle(), -1);
	m_rootNode->AddChild(m_map);

	//�A�N�^�[���C���[
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//UI���C���[
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//�v���C���[
	m_player = new Player(m_mainCamera, m_map->GetModelHandle());
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