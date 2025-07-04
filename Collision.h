#pragma once

//クラスの前方宣言
class Transform;
class BoxCollider;
class CircleCollider;

//衝突判定
class Collision
{
public:
	static bool Check(
		const Transform& transform1, const BoxCollider* box1,
		const Transform& transform2, const BoxCollider* box2
	);

	static bool Check(
		const Transform& transform1, const BoxCollider* box,
		const Transform& transform2, const CircleCollider* circle
	);

	static bool Check(
		const Transform& transform1, const CircleCollider* circle1,
		const Transform& transform2, const CircleCollider* circle2
	);
};