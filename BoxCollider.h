#pragma once
#include "Collider.h"
#include "Collision.h"
#include "Dxlib.h"

class BoxCollider : public Collider
{
public:
	Vector3 m_size;	//���E����
	Vector3 m_offset;

	//�R���X�g���N�^
	BoxCollider(const Vector3& size, const Vector3& offset = Vector3()) :
		Collider(offset),
		m_size(size),
		m_offset(offset){}

	//�Փ˔���
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collider2) const override
	{
		//�_�u���f�B�X�p�b�`�ɂ��`�󎯕ʂ�����
		return collider2->CheckCollision(transform2, transform1, this);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider* collider2) const override
	{
		//��`�Ƌ�`�̓����蔻��
		return Collision::Check(transform1, this, transform2, collider2);
	}
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider* collider2) const override
	{
		//��`�Ɖ~�`�̓����蔻��
		return Collision::Check(transform1, this, transform2, collider2);
	}

#ifdef _DEBUG
	// �`��
	virtual void Draw(const Transform& transform) const override
	{
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				if (i == 0 || j == 0) continue;

				// X
				DrawLine3D(
					Vector3(transform.position.x - m_size.x / 2 + m_offset.x, transform.position.y + m_size.y / 2 * i + m_offset.y, transform.position.z + m_size.z / 2 * j + m_offset.z),
					Vector3(transform.position.x + m_size.x / 2 + m_offset.x, transform.position.y + m_size.y / 2 * i + m_offset.y, transform.position.z + m_size.z / 2 * j + m_offset.z),
					GetColor(255, 255, 255));

				// Y
				DrawLine3D(
					Vector3(transform.position.x + m_size.x / 2 * j + m_offset.x, transform.position.y + m_size.y / 2 + m_offset.y, transform.position.z + m_size.z / 2 * i + m_offset.z),
					Vector3(transform.position.x + m_size.x / 2 * j + m_offset.x, transform.position.y - m_size.y / 2 + m_offset.y, transform.position.z + m_size.z / 2 * i + m_offset.z),
					GetColor(255, 255, 255));

				// Z
				DrawLine3D(
					Vector3(transform.position.x + m_size.x / 2 * i + m_offset.x, transform.position.y + m_size.y / 2 * j + m_offset.y, transform.position.z + m_size.z / 2 + m_offset.z),
					Vector3(transform.position.x + m_size.x / 2 * i + m_offset.x, transform.position.y + m_size.y / 2 * j + m_offset.y, transform.position.z - m_size.z / 2 + m_offset.z),
					GetColor(255, 255, 255));
			}
		}
	}
#endif
};