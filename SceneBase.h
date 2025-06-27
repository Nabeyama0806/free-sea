#pragma once

//	�V�[�����N���X
class SceneBase
{
public:
	virtual ~SceneBase() {}

	//�������z�֐�
	virtual void Preload() = 0;			//���O�ǂݍ���
	virtual void Initialize() = 0;		//������
	virtual void Finalize() = 0;		//�I��
	virtual void Update() = 0;			//�X�V
	virtual void Draw() = 0;			//�`��
};
