#include "Collision.h"
#include "Vector2.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <cmath>

using std::abs;
using std::powf;

bool Collision::Check(
	const Transform& transform1, const BoxCollider* box1,
	const Transform& transform2, const BoxCollider* box2)
{
	//各矩形の中心座標とサイズを用意
	Vector3 center1 = transform1.position + box1->m_offset * transform1.scale;
	Vector3 size1 = box1->m_size;
		  
	Vector3 center2 = transform2.position + box2->m_offset * transform2.scale;
	Vector3 size2 = box2->m_size;

	//中心座標同士の距離と、サイズ/2の合計を比較
	//それを各軸で行う
	if (abs(center1.x - center2.x) <= (size1.x + size2.x) / 2
	&&  abs(center1.y - center2.y) <= (size1.y + size2.y) / 2
	&&  abs(center1.z - center2.z) <= (size1.z + size2.z) / 2)
	{
		return true;
	}
	return false;
}

//矩形と球の衝突判定
bool Collision::Check(
	const Transform& transform1, const BoxCollider* box,
	const Transform& transform2, const CircleCollider* circle)
{
	return false;
}


bool Collision::Check(
	const Transform& transform1, const CircleCollider* circle1,
	const Transform& transform2, const CircleCollider* circle2)
{
	//各球体の中心座標
	Vector3 center1 = transform1.position;
	Vector3 center2 = transform2.position;

	//スケールを考慮した半径
	float radius1 = circle1->m_radius * transform1.scale;
	float radius2 = circle2->m_radius * transform2.scale;

	//中心間距離の2乗
	float distSq = (center1 - center2).SqrMagnitude();

	//半径の合計の2乗
	float radiusSum = radius1 + radius2;
	float radiusSumSq = radiusSum * radiusSum;

	//距離が半径の合計以下なら衝突している
	return distSq <= radiusSumSq;

}