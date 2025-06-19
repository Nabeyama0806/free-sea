#include "SceneGame.h"
#include "SceneResult.h"
#include "SoundManager.h"
#include "CharacterBase.h"
#include "BlueBird.h"
#include "GreenBird.h"
#include "RedBird.h"
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

	//�v���C���[���I�������L�����ԍ��ɉ����Đ�������L������ύX
	for (int i = 0; i < GetJoypadNum(); ++i)
	{
		CharacterBase::Type chara = static_cast<CharacterBase::Type>(m_playerChara[i]);

		switch (chara)
		{
		case CharacterBase::Type::BlueBird:
			m_characters[i] = new BlueBird(m_mainCamera, m_stage, PlayerPosition[i], i);
			break;

		case CharacterBase::Type::GreenBird:
			m_characters[i] = new GreenBird(m_mainCamera, m_stage, PlayerPosition[i], i);
			break;

		case CharacterBase::Type::RedBird:
			m_characters[i] = new RedBird(m_mainCamera, m_stage, PlayerPosition[i], i);
			
		default:
			break;
		}
		actorLayer->AddChild(m_characters[i]);
	}
	
	//BGM
	m_bgm = SoundManager::Load("Resource/Sound/bgm_game.mp3");
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
	//SoundLoader::GetInstance()->Delete("Resource/Sound/bgm_game.mp3");
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