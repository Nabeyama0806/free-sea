#pragma once

//�N���X�̑O���錾
class SceneBase;

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

private:
	SceneBase* m_scene;				//���s���̃V�[��
	SceneBase* m_nextScene;			//�J�ڐ�̃V�[��
	Phase m_phase;					//�t�F�[�Y

public:
	//�R���X�g���N�^
	SceneManager() :
		m_scene(nullptr),
		m_nextScene(nullptr),
		m_phase(Phase::Loading) {
	}

	//�V���O���g��
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}


	void Updeta();		//�X�V
	void Draw();		//�`��	
	void Release();		//�㏈��

	//�V�[���؂�ւ�
	void LoadScene(SceneBase* nextScene);
};