#include "ModelActor.h"
#include "ModelAnimation.h"
#include "Model.h"

//�R���X�g���N�^
ModelActor::ModelActor(const char* name, const char* modelFileName, const Vector3& position) :
	ActorBase(name, modelFileName, position), 
	m_model(nullptr)
{
	//�t�@�C���p�X���w�肳��Ă���΃��[�h����
	if (modelFileName)
	{
		m_model = new Model(modelFileName);
	}
}

//���\�[�X�̓ǂݍ���
void ModelActor::Load()
{
	//���f��
	if (m_model)
	{
		m_model->Load();
	}

	////�Փ˔���̒ǉ�
	//if (m_collider)
	//{
	//	ModelActorCollision::GetInstance()->Register(this);
	//}
}

//���\�[�X�̉��
void ModelActor::Release()
{
	//���f��
	if (m_model)
	{
		delete m_model;
		m_model = nullptr;
	}
	
	//�Փ˔��肩�珜�O
	/*if (m_collider)
	{
		ModelActorCollision::GetInstance()->Remove(this);
		delete m_collider;
		m_collider = nullptr;
	}*/

	//�j������
	OnDestroy();
}

//�`��
void ModelActor::Draw()
{
	//���f��
	if (m_model)
	{
		m_model->Draw(m_transform);
	}
}

//�j������
void ModelActor::OnDestroy()
{
	//�������Ȃ�
}

//�q�m�[�h���܂ލX�V
void ModelActor::TreeUpdate()
{
	//�{����Update
	Node::TreeUpdate();
	
	//���f��
	if (m_model)
	{
		m_model->Update();
	}
}