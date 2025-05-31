#pragma once
#include "Vector3.h"
#include "Transform.h"

//�N���X�̑O���錾
class BoxCollider;
class CircleCollider;

class Collider
{
public:
	//���S���W����̃Y��
	Vector3 m_offset;

	//�R���X�g���N�^
	Collider(const Vector3& offset) :
		m_offset(offset) {}

	//�Փ˔���
	//�_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ��s��
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collision2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider* collision2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider* collision2) const = 0;

#ifdef _DEBUG
	//Collider�̕`��
	virtual void Draw(const Transform& transform) const = 0;
#endif
};