#include "GameMain.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "GameConfig.h"
#include "Screen.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "ModelActorCollision.h"
#include "BulletData.h"
#include "Input.h"
#include "Time.h"
#include "Fade.h"
#include "Debug.h"
#include "DxLib.h"

//�f�X�g���N�^
GameMain::~GameMain()
{
	//����X�N���[���̔j��
	DeleteGraph(m_screen);

	//�f�o�b�O�R���\�[���̏I��
	Debug::Finalize();

	// Effekseer �I��
	Effkseer_End();

	// DxLib �I��
	DxLib_End();
}

//���C�����[�v
void GameMain::Run()
{
	SetMainWindowText(GameConfig::Title); //�E�B���h�E�^�C�g��
	SetAlwaysRunFlag(GameConfig::AlwayRunFlag); //��A�N�e�B�u���ɓ��삷��
	ChangeWindowMode(GameConfig::WindowMode); //�E�B���h�E���[�h�ŋN��
	SetGraphMode(Screen::Width, Screen::Height, GameConfig::ColorBit); //�E�B���h�E�T�C�Y
	SetBackgroundColor(0, 0, 0);

	//DX���C�u�����̏�����
	if (DxLib_Init())
	{
		throw - 1;
	}

	//�G�t�F�N�g
	EffectManager::GetInstance()->Initialize();

	//�V�[���N��
	SceneManager::GetInstance()->LoadScene(new SceneTitle());

	//�X�N���[���̍쐬
	m_screen = MakeScreen(Screen::Width, Screen::Height);

	//�e�f�[�^�̓ǂݍ���
	BulletData::GetInstance()->LoadCSV();

	//�Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		//���̓V�X�e���̍X�V
		Input::GetInstance()->Update();

		//���Ԃ̍X�V
		Time::GetInstance()->Update();

		//ESC�L�[�������ꂽ��I��
		if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE))
		{
			if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE))
			{
				break;
			}
		}

		//�f�o�b�O�R���\�[���̏�����
		Debug::Initialize();

		//�V�[���̍X�V
		SceneManager::GetInstance()->Updeta();

		//�Փ˔���
		ModelActorCollision::GetInstance()->Update();

		//����X�N���[���ɕ`��
		SetDrawScreen(m_screen);

		//��ʂɕ`����Ă�����̂�S�ď���
		ClearDrawScreen();

		//�V�[���̕`��
		SceneManager::GetInstance()->Draw();

		//�G�t�F�N�g�̍X�V
		EffectManager::GetInstance()->Update();

		//�G�t�F�N�g�̕`��
		EffectManager::GetInstance()->Draw();

		//�t�F�[�h
		Fade::GetInstance()->Update(m_screen);

		//����X�N���[���𗠉�ʂɕ`��
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, m_screen, false);

		//����ʂƕ\��ʂ��Ђ�����Ԃ�
		ScreenFlip();
	}

	//�V�[���̔j��
	SceneManager::GetInstance()->Release();
}