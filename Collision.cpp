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
	//�e��`�̒��S���W�ƃT�C�Y��p��
	Vector3 center1 = transform1.position + box1->m_offset * transform1.scale;
	Vector3 size1 = box1->m_size * transform1.scale;
		  
	Vector3 center2 = transform2.position + box2->m_offset * transform2.scale;
	Vector3 size2 = box2->m_size * transform2.scale;

	//���S���W���m�̋����ƁA�T�C�Y/2�̍��v���r
	//������e���ōs��
	if (abs(center1.x - center2.x) <= (size1.x + size2.x) / 2
	&&  abs(center1.y - center2.y) <= (size1.y + size2.y) / 2
	&&  abs(center1.z - center2.z) <= (size1.z + size2.z) / 2)
	{
		return true;
	}
	return false;
}

bool Collision::Check(
	const Transform& transform1, const BoxCollider* box,
	const Transform& transform2, const CircleCollider* circle)
{
	////��`�̍���E�E���̍��W�A�~�̒��S���W�Ɣ��a��p��
	//Vector3 boxTopLeft = transform1.position + box->offset * transform1.scale - box->m_size * transform1.scale / 2;
	//Vector3 boxBottomRIght = boxTopLeft + box->m_size * transform1.scale;

	//Vector3 circlePos = transform2.position + circle->offset * transform2.scale;
	//float circleRadius = circle->radius * transform2.scale;

	////��`���~�̔��a���L�����͈͂ɁA�~�̒��S�_�����Ȃ����ǂ���
	//if (boxTopLeft.x - circleRadius > circlePos.x
	//	|| boxBottomRIght.x + circleRadius < circlePos.x
	//	|| boxTopLeft.y - circleRadius > circlePos.y
	//	|| boxBottomRIght.y + circleRadius < circlePos.y)
	//{
	//	return false;
	//}

	////������g���e���̒l��p��
	//float left2Pow = powf(boxTopLeft.x - circlePos.x, 2);
	//float right2Pow = powf(boxBottomRIght.x - circlePos.x, 2);
	//float top2Pow = powf(boxTopLeft.y - circlePos.y, 2);
	//float bottom2Pow = powf(boxBottomRIght.y - circlePos.y, 2);
	//float radius2Pow = powf(circleRadius, 2);

	////����̓����蔻��
	//if (boxTopLeft.x > circlePos.x && boxTopLeft.y > circlePos.y
	//	&& !(left2Pow + top2Pow < radius2Pow))
	//{
	//	return false;
	//}

	////�E��̓����蔻��
	//if (boxBottomRIght.x < circlePos.x && boxTopLeft.y > circlePos.y
	//	&& !(right2Pow + top2Pow < radius2Pow))
	//{
	//	return false;
	//}

	////�����̓����蔻��
	//if (boxTopLeft.x > circlePos.x && boxBottomRIght.y < circlePos.y
	//	&& !(left2Pow + bottom2Pow < radius2Pow))
	//{
	//	return false;
	//}

	////�E���̓����蔻��
	//if (boxBottomRIght.x < circlePos.x && boxBottomRIght.y < circlePos.y
	//	&& !(right2Pow + bottom2Pow < radius2Pow))
	//{
	//	return false;
	//}

	return false;
}

bool Collision::Check(
	const Transform& transform1, const CircleCollider* circle1,
	const Transform& transform2, const CircleCollider* circle2)
{
	//�e���̂̒��S���W
	Vector3 center1 = transform1.position;
	Vector3 center2 = transform2.position;

	//���S�ԋ�����2��
	float distSq = (center1 - center2).SqrMagnitude();

	//���a�̍��v��2��
	float radiusSum = circle1->m_radius + circle2->m_radius;
	float radiusSumSq = radiusSum * radiusSum;

	//���������a�̍��v�ȉ��Ȃ�Փ˂��Ă���
	return distSq <= radiusSumSq;
}