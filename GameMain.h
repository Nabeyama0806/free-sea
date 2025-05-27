#pragma once

class SceneManager;

//�Q�[�����C�����[�v�N���X
class GameMain
{
private:
	SceneManager* m_sceneManager;	//�V�[���J��
	int m_screen;	//����X�N���[��
public:
	//�R���X�g���N�^(���s���Ɏ����I�ɌĂяo�����֐�)
	GameMain() :
		m_sceneManager(nullptr),
		m_screen(0)
	{
	}

	//�f�X�g���N�^
	virtual ~GameMain();

	//���C�����[�v���s
	void Run();
};