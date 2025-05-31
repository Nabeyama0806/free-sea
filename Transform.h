#pragma once
#include "Vector3.h"
#include "Quaternion.h"

class Transform
{
public:
	Vector3 position;		//座標
	Quaternion rotation;	//角度(ラジアン)
	float scale;			//拡縮

	Transform() :
		scale(1) {}
};
