#pragma once

//�Q�[�����C�����[�v�N���X
class GameMain
{
private:
	int m_screen;	//����X�N���[��

public:
	//�R���X�g���N�^(���s���Ɏ����I�ɌĂяo�����֐�)
	GameMain() :
		m_screen(0)
	{
	}

	//�f�X�g���N�^
	virtual ~GameMain();

	//���C�����[�v���s
	void Run();
};