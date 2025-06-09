#pragma once
#include "Collider.h"
#include "Collision.h"
#include "Dxlib.h"

class CircleCollider : public Collider
{
public:
	float m_radius;	//���a

	//�R���X�g���N�^
	CircleCollider(float radius, const Vector3& offset = Vector3()) :
		Collider(offset),
		m_radius(radius)
	{
	}

	//�Փ˔���
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collider2) const override
	{
		//�_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ�����
		return collider2->CheckCollision(transform2, transform1, this);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider* collider2) const override
	{
		//��`�Ɖ~�`�̏Փ˔���
		return Collision::Check(transform2, collider2, transform1, this);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider* collider2) const override
	{
		//�~�`�Ɖ~�`�̏Փ˔���
		return Collision::Check(transform1, this, transform2, collider2);
	}

#ifdef _DEBUG
	//�`��
	virtual void Draw(const Transform& transform) const override
	{
		DrawSphere3D(transform.position + m_offset, m_radius, 6, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
	}
#endif
};