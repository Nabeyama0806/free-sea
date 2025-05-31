#pragma once
#include "ActorBase.h"
#include "Transform.h"
#include "Collider.h"
#include "Model.h"
#include <string>

class Model;
class Effect;

class ModelActor : public ActorBase
{
protected:
	static constexpr Vector3 ColliderSize = Vector3(100, 100, 100);	
	static constexpr Vector3 Scale = Vector3(25, 25, 25);
	
	Model* m_model;	
	Effect* m_effect;
	Collider* m_collider;
	Vector3 m_effectOffset;

	virtual void Load() override;		//���\�[�X�̓ǂݍ���
	virtual void Release() override;	//���\�[�X�̉��
	virtual void Draw() override;		//�`��
	virtual void OnDestroy() override;	//�I�u�W�F�N�g�̍폜

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

	//�Փ˔���̌`����擾
	const Collider* GetCollider() const
	{
		return m_collider;
	}

	//���f���̎��ʔԍ����擾
	const int GetModelHandle()
	{
		return m_model->GetModelHandle();
	}
};