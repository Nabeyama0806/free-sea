#pragma once
#include "Vector3.h"
#include "Quaternion.h"

class Transform
{
public:
	Vector3 position;		//���W
	Quaternion rotation;	//�p�x(���W�A��)
	float scale;			//�g�k

	Transform() :
		scale(1) {}
};
