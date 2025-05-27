#pragma once
#include "ActorBase.h"
#include "Transform.h"
#include <string>

class Model;

class ModelActor : public ActorBase
{
protected:
	static constexpr Vector3 ColliderSize = Vector3(100, 100, 100);			// �R���C�_�[�̃T�C�Y
	static constexpr Vector3 Scale = Vector3(25, 25, 25);
	
	Model* m_model;	//3D���f��	

	virtual void Load() override;		//���\�[�X�̓ǂݍ���
	virtual void Release() override;	//���\�[�X�̉��
	virtual void Draw() override;		//�`��
	virtual void OnDestroy();			//�I�u�W�F�N�g�̍폜

public:
	//�R���X�g���N�^
	ModelActor(
		const char* name,
		const char* modelFileName = nullptr,
		const Vector3& position = Vector3()
	);

	//�q�m�[�h���܂ލX�V
	virtual void TreeUpdate() override;

	//�Փ˃C�x���g
	virtual void OnCollision(const ModelActor* other) {}
};