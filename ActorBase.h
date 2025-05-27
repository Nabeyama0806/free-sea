#pragma once
#include "Node.h"
#include "Transform.h"
#include <string>

class ActorBase : public Node
{
protected:
	std::string m_name;				//�I�u�W�F�N�g��
	Transform m_transform;			//�p�����

	virtual void Load() override = 0;		//���\�[�X�̓ǂݍ���
	virtual void Release() override = 0;	//���\�[�X�̊J��
	virtual void Draw() override = 0;		//���\�[�X�̊J��

public:
	//�R���X�g���N�^
	ActorBase(const char* name,
		const char* textureName = nullptr,
		const Vector3& position = Vector3()) :
		m_name(name)
	{
		//���W�̐ݒ�
		m_transform.position = position;
	}	

	//�q�m�[�h���܂ލX�V
	virtual void TreeUpdate() override = 0;

	//�p���̎擾
	const Transform& GetTransform() const
	{
		return m_transform;
	}

	//���W�̎擾
	const Vector3& GetPosition() const
	{
		return m_transform.position;
	}

	//���O�̎擾
	const std::string& GetName()const
	{
		return m_name;
	}

	//�傫���̕ύX
	void ChangeScale(float scale) 
	{
		m_transform.scale *= scale; 
	}
};