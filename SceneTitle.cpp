#include "SceneTitle.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include"SceneGame.h"
#include "CharacterBase.h"
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
	
	//�摜
	/*m_sprite = new Sprite();
	for (int i = 0; i < static_cast<int>(CharacterBase::Type::Length); ++i)
	{
		m_sprite->Register(CharaTextureName[i], FilePath[i]);
	}*/
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
	//�摜�̍X�V
	//m_sprite->Update();

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

		for (int i = 0; i < GetJoypadNum(); ++i)
		{
			//����{�^���������ꂽ��Q�[���J�n
			if (InputSystem::GetInstance()->IsDecision(static_cast<InputSystem::ActionMap>(i)))
			{
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

	//m_sprite->Draw(m_transform);
}