#include "SceneTitle.h"
#include "SceneGame.h"
#include "CharacterBase.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Input.h"
#include "Debug.h"
#include "DxLib.h"

//������
void SceneTitle::Initialize()
{
	m_transform.position = Screen::Center;
	m_transform.scale = 0.2f;

	//�m�[�h
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title.png", Screen::Center));

	//�ڑ�����Ă���p�b�h�����擾
	m_padAmount = GetJoypadNum();

	//�ڑ�����Ă���p�b�h�̐������z��̗v�f����ǉ�
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_select.push_back(0);
	}

	//�摜�̓ǂݍ���
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i] = new Sprite();
		m_sprites[i]->gridSize = Vector2(1920, 1032);
		for (int j = 0; j < static_cast<int>(CharacterBase::Type::Length); ++j)
		{
			m_sprites[i]->Register(TextureName[j], SpriteAnimation(CharacterImage[j]));
			m_sprites[i]->Load();
		}
	}

	//BGM
	m_bgm = SoundManager::Load("Resource/sound/bgm_title.mp3");
	SoundManager::Play(m_bgm, DX_PLAYTYPE_LOOP);
}

//�I��
void SceneTitle::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//�X�V
SceneBase* SceneTitle::Update()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	//�摜�̕\��
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i]->Update();
	}
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i]->Play(TextureName[m_select[i]]);
	}

	//�����ꂩ�̃L�[�������ꂽ��Q�[���V�[���ֈړ�
	switch (m_phase)
	{
	case SceneTitle::Phase::Home:
		if (Input::GetInstance()->IsAnyKeyDown())
		{
			m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title_select.png", Screen::Center));
			m_phase = Phase::Select;
		}
		break;

	case SceneTitle::Phase::Select:
		//�v���C���[���Ƃ̃L�����I��
		for (int i = 0; i < m_padAmount; ++i)
		{
			InputSystem::ActionMap actionMap = static_cast<InputSystem::ActionMap>(i);

			//�L�����I��
			if (InputSystem::GetInstance()->SelectLeft(actionMap))	m_select[i]--;
			if (InputSystem::GetInstance()->SelectRight(actionMap)) m_select[i]++;

			//�͈͓��ɒ���
			if (m_select[i] <= 0) m_select[i] = static_cast<int>(CharacterBase::Type::Length);
			if (m_select[i] >= static_cast<int>(CharacterBase::Type::Length)) m_select[i] = 0;

			//����{�^���������ꂽ��Q�[���J�n
			if (InputSystem::GetInstance()->IsDecision(actionMap))
			{
				SoundManager::SoundStop(m_bgm);
				m_phase = Phase::GameStart;
			}
		}
		break;

	case SceneTitle::Phase::GameStart:
		return new SceneGame(m_select);
		break;

	default:
		break;
	}

	return this;
}

//�`��
void SceneTitle::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();

	//�z�[����ʂł͉����`�悵�Ȃ�
	if (m_phase == SceneTitle::Phase::Home) return; 

	//�摜�̕`��
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_transform.position = Screen::Center + DrawPosOffset[i];
		m_sprites[i]->Draw(m_transform);
	}
}