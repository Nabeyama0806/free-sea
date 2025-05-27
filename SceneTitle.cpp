#include "SceneTitle.h"
#include"SceneGame.h"
#include "Screen.h"
#include "Input.h"
#include "DxLib.h"

//������
void SceneTitle::Initialize()
{
	m_rootNode = new Node();

	//�w�i
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
	if (Input::GetInstance()->IsAnyKeyDown())
	{
		return new SceneGame();
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