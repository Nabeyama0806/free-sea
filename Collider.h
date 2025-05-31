#pragma once
#include "Vector3.h"
#include "Transform.h"
#include "Collision.h"

//クラスの前方宣言
class BoxCollider;
class CircleCollider;
class ColliderResult;

class Collider
{
public:
	int m_mapModelHandle;
	int m_frameIndex;
   
	ColliderResult* m_colliderResult;
	Vector3 m_offset;

	//コンストラクタ
	Collider(const Vector3& offset) :
		m_colliderResult(nullptr),
		m_offset(offset){}

	//衝突判定
	//ダブルディスパッチによる形状識別を行う
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const Collider* collision2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const BoxCollider* collision2) const = 0;
	virtual bool CheckCollision(const Transform& transform1, const Transform& transform2, const CircleCollider* collision2) const = 0;

	//ステージ(ポリゴン)との当たり判定
	virtual ColliderResult* CheckHitPolygon(const Transform& transform) const 
	{
		return nullptr;
	}

#ifdef _DEBUG
	//Colliderの描画
	virtual void Draw(const Transform& transform) const = 0;
#endif
};