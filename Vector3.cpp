#include "DxLib.h"
#include "Vector3.h"
#include "Vector2.h"
#include <cmath>

//Vector2�ւ̃L���X�g
Vector3::operator Vector2() const
{
	return Vector2(x, y);
}

//VECTOR�ւ̃L���X�g
Vector3::operator VECTOR() const
{
	VECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}