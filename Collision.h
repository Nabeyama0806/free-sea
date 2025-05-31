#pragma once

//ƒNƒ‰ƒX‚Ì‘O•ûéŒ¾
class Transform;
class BoxCollider;
class CircleCollider;

//Õ“Ë”»’è
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