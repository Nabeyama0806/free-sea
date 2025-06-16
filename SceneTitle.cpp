#include "SceneTitle.h"
#include "SceneGame.h"
#include "CharacterBase.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Input.h"
#include "DxLib.h"

//������
void SceneTitle::Initialize()
{
	//�m�[�h
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title.png", Screen::Center));

	//�ڑ�����Ă���p�b�h�����擾
	m_padAmount = GetJoypadNum();

	//�ڑ�����Ă���p�b�h�̐������z��̗v�f����ǉ�
	for (int i = 0; i < GetJoypadNum(); ++i)
	{
		m_select.push_back(i);
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
		for (int i = 0; i < GetJoypadNum(); ++i)
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

	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	return this;
}

//�`��
void SceneTitle::Draw()
{
	//�m�[�h�̕`��
	m_rootNode->TreeDraw();
}