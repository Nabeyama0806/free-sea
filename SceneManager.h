#pragma once
#include "Transform.h"
#include "Screen.h"

//�N���X�̑O���錾
class SceneBase;
class Sprite;

//�V�[���J�ڃN���X
class SceneManager
{
private:
	//�t�F�[�Y
	enum class Phase
	{
		Run,		//���s��
		FadeOut,	//�t�F�[�h�A�E�g
		Loading,	//���[�h��
		Transition,	//�J��
	};

	Phase m_phase;

private:
	SceneBase* m_scene;				//���s���̃V�[��
	SceneBase* m_nextScene;			//�J�ڐ�̃V�[��
	Sprite*	m_sprite;				//�X�v���C�g
	Transform m_transform;

public:
	//�R���X�g���N�^
	SceneManager();

	//�V���O���g��
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}


	void Update();		//�X�V
	void Draw();		//�`��	
	void Release();		//�㏈��

	//�V�[���؂�ւ�
	void LoadScene(SceneBase* nextScene);
};