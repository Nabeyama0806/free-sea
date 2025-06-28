#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "SpriteLoader.h"
#include "ModelLoader.h"
#include "Bullet.h"
#include "Character.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Transform.h"
#include "Camera.h"
#include "Stage.h"
#include "DxLib.h"

//���O�ǂݍ���
void SceneGame::Preload()
{
	//�摜�̃v�����[�h
	for (const char* modelPath : CharacterIconFilePath)
	{
		SpriteLoader::GetInstance()->Load(modelPath);
	}

	//���f���̃v�����[�h
	for (const char* modelPath : ModelPreload)
	{
		ModelLoader::GetInstance()->Load(modelPath);
	}
}

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
	IsLastCharacter();

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
void SceneGame::IsLastCharacter() const 
{
	//�L�����N�^�[�̐��������J�E���g
	Character* lastCharacter = nullptr;
	int aliveCount = 0;
	for (const auto& character : m_characters) 
	{ 
		//�L�����N�^�[�����݂��Ȃ��ꍇ�̓X�L�b�v
		if (!character) continue;

		//�Ō�̐����L�����N�^�[����ۑ�
		if (character->IsAlive())
		{
			lastCharacter = character;
			aliveCount++;
		}

		//2�l�ȏ㐶��
		if (aliveCount >= 2) return;
	}
	
	//�����L�����N�^�[��1�l�Ȃ烊�U���g�֑J��
	if (aliveCount == 1) SceneManager:: GetInstance()->LoadScene(new SceneResult(lastCharacter));
}
