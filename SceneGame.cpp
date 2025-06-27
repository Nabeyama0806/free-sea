#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Bullet.h"
#include "Character.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Transform.h"
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

	//��������L�����̕���
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_characters[i] = new Character(m_mainCamera, m_stage, PlayerPosition[i], i, m_playerBullets[i]);
		actorLayer->AddChild(m_characters[i]);
	}

	//�L�����N�^�[�A�C�R���̓ǂݍ���
	m_sprite = new Sprite();
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprite->Register(CharacterIconName[i], SpriteAnimation(CharacterIconFilePath[i]));
		m_sprite->Load();
	}
	m_transform.scale = 0.6f;
	
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
	SoundManager::SoundStop(m_bgm);
}

//�X�V
void SceneGame::Update()
{
	//�L�����N�^�[���c��1�l�Ȃ烊�U���g�֑J��
	//if (IsLastCharacter()) SceneManager::GetInstance()->LoadScene(new SceneResult(0));

	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();
	m_sprite->Update();
}

//�`��
void SceneGame::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();

	//�L�����N�^�[�A�C�R���̕`��
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_transform.position = CharacterIconPosition[i];
		m_sprite->Play(CharacterIconName[i]);
		m_sprite->Draw(m_transform);
	}
}

//�Ō�̃L�����N�^�[���ǂ����𔻒�
bool SceneGame::IsLastCharacter() const 
{
	//�L�����N�^�[�̐��������J�E���g
	int aliveCount = 0;
	for (const auto& character : m_characters) 
	{ 
		//�L�����N�^�[�����݂��Ȃ��ꍇ�̓X�L�b�v
		if (!character) continue;

		//2�l�ȏ㐶��
		if (aliveCount >= 2) return false; 

		//�Ō�̐����L�����N�^�[����ۑ�
		if (character->IsAlive()) aliveCount++;
	}

	//�Ō�̃L�����N�^�[
	return aliveCount == 1;
}
