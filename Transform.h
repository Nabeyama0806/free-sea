#pragma once
#include "Vector3.h"
#include "Quaternion.h"

class Transform
{
public:
	Vector3 position;		//���W
	Quaternion rotation;	//�p�x(���W�A��)
	Vector3 scale;			//�g�k

	Transform() :
		scale(Vector3(1, 1, 1)) {}
};
