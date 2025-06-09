#include "SceneGame.h"
#include "SceneResult.h"
#include "SoundLoader.h"
#include "SoundManager.h"
#include "BlueBird.h"
#include "GreenBird.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Camera.h"
#include "Stage.h"
#include "DxLib.h"

//������
void SceneGame::Initialize()
{
	//�O���[�o�����C�g
	SetGlobalAmbientLight(GetColorF(1, 1, 1, 0));

	//���[�g
	m_rootNode = new Node();

	//���C���J����
	m_mainCamera = new Camera();
	m_rootNode->AddChild(m_mainCamera);

	//�A�N�^�[���C���[
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//�X�J�C�{�b�N�X
	ModelActor* skybox = new ModelActor("Skybox", "Resource/Model/Skybox.mv1");
	skybox->ChangeScale(10000);
	actorLayer->AddChild(skybox);

	//�X�e�[�W
	m_stage = new Stage();
	MV1SetupCollInfo(m_stage->GetModelHandle(), m_stage->GetFrameIndex());
	actorLayer->AddChild(m_stage);
	m_mainCamera->SetLookAt(m_stage);

	//UI���C���[
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//�v���C���[
	m_blueBird = new BlueBird(m_mainCamera, m_stage, PlayerPosition[0], 1);
	actorLayer->AddChild(m_blueBird);

	m_greenBird = new GreenBird(m_mainCamera, m_stage, PlayerPosition[1], 0);
	actorLayer->AddChild(m_greenBird);
	
	//BGM
	m_bgm = SoundLoader::GetInstance()->Load("Resource/Sound/bgm_game.mp3");
	SoundManager::Play(m_bgm, DX_PLAYTYPE_LOOP);
}

//�I��
void SceneGame::Finalize()
{
	//�m�[�h�̍폜
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;

	//BGM
	SoundLoader::GetInstance()->Delete("Resource/Sound/bgm_game.mp3");
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