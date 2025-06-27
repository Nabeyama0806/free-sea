#include "SceneResult.h"
#include "SceneTitle.h"
#include "SpriteActor.h"
#include "Screen.h"
#include "Input.h"
#include "Time.h"

//������
void SceneResult::Initialize()
{
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new SpriteActor("Result", "Resource/Texture/result.png", Screen::Center));
}

//�I������
void SceneResult::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//�X�V
SceneBase* SceneResult::Update()
{
	if (m_waitTransitionTime > 0)
	{
		m_waitTransitionTime -= Time::GetInstance()->GetDeltaTime();
	}

	//�����ꂩ�̃L�[�������ꂽ��^�C�g����ʂɑJ��
	if (m_waitTransitionTime <= 0 && Input::GetInstance()->IsAnyKeyDown())
	{
		return new SceneTitle();
	}

	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	return this;
}

//�`��
void SceneResult::Draw()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeDraw();
}