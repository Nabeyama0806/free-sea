#include "SceneManager.h"
#include "SceneBase.h"
#include "Sprite.h"
#include "Fade.h"
#include "Time.h"
#include "DxLib.h"

//�R���X�g���N�^
SceneManager::SceneManager() :
	m_scene(nullptr),
	m_nextScene(nullptr),
	m_sprite(nullptr),
	m_elapsedTime(0),
	m_phase(Phase::Loading)
{
	//�p�����
	m_transform.position = Screen::Center;

	//�X�v���C�g�̓ǂݍ���
	m_sprite = new Sprite();
	m_sprite->Register("Resource/Texture/loading.png");
	m_sprite->Load();
}

//�㏈��
void SceneManager::Release()
{
	//���s���̃V�[���ƑJ�ڐ�̃V�[���������Ȃ�A���ddelete���Ȃ�
	if (m_scene == m_nextScene)
	{
		m_nextScene = nullptr;
	}

	//���s���̃V�[���̔j��
	if (m_scene != nullptr)
	{
		m_scene->Finalize();
		delete m_scene;
		m_scene = nullptr;
	}

	//�J�ڐ�V�[���̔j��
	if (m_nextScene != nullptr)
	{
		m_nextScene->Finalize();
		delete m_nextScene;
		m_nextScene = nullptr;
	}
}

//�X�V
void SceneManager::Update()
{
	switch (m_phase)
	{
		//���s��
	case Phase::Run:
		//���s���̃V�[���̍X�V
		m_scene->Update();

		//�J�ڐ�̃V�[�������s���̃V�[���ƈقȂ�ꍇ�ɑJ�ڂ���
		if (m_nextScene != m_scene)
		{
			//�t�F�[�h�A�E�g�J�n
			m_phase = Phase::FadeOut;
			Fade::GetInstance()->StartFadeOut();
		}
		break;

		//�t�F�[�h�A�E�g
	case Phase::FadeOut:
		//�t�F�[�h�A�E�g���I���܂őҋ@
		if (Fade::GetInstance()->IsFade()) break;

		//�t�F�[�h���I������̂ŃV�[���J�ڂ���
		m_phase = Phase::Loading;
		break;

	case Phase::Loading:
		//�񓯊����[�h�̊J�n
		SetUseASyncLoadFlag(TRUE);
		m_nextScene->Preload();
		m_sprite->Update();

		//���[�h���Ԃ��o�߂�����t�F�[�Y��ύX
		m_elapsedTime += Time::GetInstance()->GetDeltaTime();
		if (m_elapsedTime < LoadingTime) break;
		if (GetASyncLoadNum() != 0) break;

		//�񓯊����[�h���I�����Ă���V�[���J��
		m_elapsedTime = 0;
		SetUseASyncLoadFlag(FALSE);
		m_phase = Phase::Transition;

		//�V�[���J��
	case Phase::Transition:

		//���s���̃V�[��������Δj������
		if (m_scene)
		{
			m_scene->Finalize();
			delete m_scene;
			m_scene = nullptr;
		}

		//�J�ڐ�̃V�[�������s���̃V�[���ɂ���
		m_scene = m_nextScene;
		m_scene->Initialize();

		//�t�F�[�h�C��
		Fade::GetInstance()->StartFadeIn(0.2f);

		m_phase = Phase::Run;
		break;
	}
}

//�`��
void SceneManager::Draw()
{
	switch (m_phase)
	{
	case Phase::Run:
	case Phase::FadeOut:
		if (m_scene) m_scene->Draw();
		break;

	case Phase::Loading:
		m_sprite->Draw(m_transform); //���[�h���̃X�v���C�g��`��
		break;
	}
}

//�V�[���؂�ւ�
void SceneManager::LoadScene(SceneBase* nextScene)
{
	m_nextScene = nextScene;
}