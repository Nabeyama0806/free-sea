#pragma once

//�N���X�̑O���錾
class Transform;
class BoxCollider;
class CircleCollider;

//�Փ˔���
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