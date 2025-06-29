#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "BulletData.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Debug.h"
#include "DxLib.h"

//���O�ǂݍ���
void SceneTitle::Preload()
{
	//���f���̃v�����[�h
	for (const char* modelPath : ModelPreload)
	{
		ModelLoader::GetInstance()->Load(modelPath);
	}
}

//������
void SceneTitle::Initialize()
{
	//�p�����
	m_transform.position = Screen::Center;
	m_transform.scale = 0.33f;

	//�m�[�h
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title.png", Screen::Center));

	//�^�C�g�����S
	m_rootNode->AddChild(new SpriteActor("TitleLogo", "Resource/Texture/title_logo.png", Screen::Center));

	//�ڑ�����Ă���p�b�h�̐������z��̗v�f����ǉ�
	for (int i = 0; i < InputSystem::GetInstance()->GetPadAmount(); ++i)
	{
		m_select.push_back(0);
	}

	//�摜�̓ǂݍ���
	for (int i = 0; i < InputSystem::MaxPadAmount; ++i)
	{
		m_sprites[i] = new Sprite();
		m_sprites[i]->gridSize = Vector2(1080, 1080);
		for (int j = 0; j < BulletData::GetInstance()->GetBulletListSize(); ++j)
		{
			//�e�̃f�[�^�ɂ��閼�O�ƃt�@�C���p�X���Q�Ƃ�����
			m_sprites[i]->Register(TextureName[j], SpriteAnimation(BulletImage[j]));
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
void SceneTitle::Update()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	//�p�b�h�̐ڑ������X�V
	m_padAmount = InputSystem::GetInstance()->GetPadAmount();

	//�����ꂩ�̃L�[�������ꂽ��Q�[���V�[���ֈړ�
	switch (m_phase)
	{
	case SceneTitle::Phase::Home:
		if (InputSystem::GetInstance()->IsAnyKeyDown())
		{
			SoundManager::Play("Resource/Sound/se_next.mp3");
			m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title_select.png", Screen::Center));
			m_phase = Phase::Select;
		}
		break;

	case SceneTitle::Phase::Select:
		//�e�v���C���[�̒e�I��
		for (int i = 0; i < m_padAmount; ++i)
		{
			//�p�b�h�̐ڑ����������Ă���Βǉ�
			if (i >= m_select.size()) m_select.push_back(0);

			InputSystem::ActionMap actionMap = static_cast<InputSystem::ActionMap>(i);
			if (InputSystem::GetInstance()->SelectLeft(actionMap))
			{
				m_select[i]--;
				SoundManager::Play("Resource/Sound/se_next.mp3");
			}

			if (InputSystem::GetInstance()->SelectRight(actionMap))
			{
				m_select[i]++;
				SoundManager::Play("Resource/Sound/se_next.mp3");
			}

			//�͈͓��ɒ���
			if (m_select[i] < 0) m_select[i] = BulletData::GetInstance()->GetBulletListSize() - 1;
			if (m_select[i] > BulletData::GetInstance()->GetBulletListSize() - 1) m_select[i] = 0;

			//����{�^���������ꂽ��Q�[���J�n
			if (InputSystem::GetInstance()->IsDecision(actionMap))
			{
				SoundManager::SoundStop(m_bgm);
				SceneManager::GetInstance()->LoadScene(new SceneGame(m_select));
			}
		}
		break;
	}

	//�z�[����ʂł͕\�����Ȃ�
	if (m_phase == SceneTitle::Phase::Home) return;

	//�摜�̍X�V
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i]->Update();
		m_sprites[i]->Play(TextureName[m_select[i]]);
	}
}

//�`��
void SceneTitle::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();

	//�z�[����ʂł͕`�悵�Ȃ�	
	if (m_phase == SceneTitle::Phase::Home) return; 

	//�摜�̕`��
	for (int i = 0; i < m_padAmount; ++i)
	{
		//�摜�̕`��
		m_transform.position = Screen::Center + DrawPosOffset[i];
		m_sprites[i]->Draw(m_transform);
	}
}