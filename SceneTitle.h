#pragma once
#include "SceneBase.h"
#include "Node.h"

class Node;

//�^�C�g���V�[��
class SceneTitle : public SceneBase
{
private:
	Node* m_rootNode;

public:
	//�R���X�g���N�^
	SceneTitle() :
		m_rootNode(nullptr){}

	virtual void Initialize() override;				//������
	virtual void Finalize() override;				//�I��
	virtual SceneBase* Update() override;			//�X�V
	virtual void Draw() override;					//�`��
};