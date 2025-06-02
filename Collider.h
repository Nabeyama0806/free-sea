#pragma once
#include "Vector3.h"
#include "Transform.h"
#include "Collision.h"

//クラスの前方宣言
class BoxCollider;
class CircleCollider;

class Collider
{
public:
	int m_mapModelHandle;
	int m_frameIndex;
	Vector3 m_offset;

	//コンストラクタ
	Collider(const Vector3& offset) :
		m_offset(offset),
		m_mapModelHandle(0),
		m_frameIndex(0){}

	//衝突判定
	//ダブルディスパッチによる形状識別を行う
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collision2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider* collision2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider* collision2) const = 0;

#ifdef _DEBUG
	//Colliderの描画
	virtual void Draw(const Transform& transform) const = 0;
#endif
};