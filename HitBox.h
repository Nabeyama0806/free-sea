#pragma once
#include "ModelActor.h"
#include "CircleCollider.h"

class HitBox : public ModelActor
{
public:
	//�R���X�g���N�^
	HitBox() :
		ModelActor("HitBox")
	{
		m_collider = new CircleCollider(100, Vector3(0, 75, 0));
	}
};