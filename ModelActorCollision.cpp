#include "ModelActorCollision.h"
#include "ModelActor.h"
#include "ColliderResult.h"
#include "Collider.h"

//�X�V
void ModelActorCollision::Update()
{
	std::list<ModelActor*> actorList(m_actorList);

	//��������ŏՓ˔���
	for (auto it1 = actorList.begin(); it1 != actorList.end(); it1++)
	{
		for (auto it2 = it1; it2 != actorList.end(); it2++)
		{
			//�C�e���[�^����Actor*�����o��
			ModelActor* actor1 = *it1;
			ModelActor* actor2 = *it2;

			//�Փ˔���̌`�󂪂Ȃ�������X�L�b�v
			if (!actor1->GetCollider()) continue;
			if (!actor2->GetCollider()) continue;

			//�������g�̓X�L�b�v
			if (actor1 == actor2) continue;

			//�X�e�[�W�Ƃ̓����蔻��
			const ColliderResult* result1;
			result1 = actor1->GetCollider()->CheckHitPolygon(actor1->GetTransform());
			if (result1 && result1->m_hitFlag)
			{
				actor1->OnHitPolygon(result1);
			}
			const ColliderResult* result2;
			result2 = actor2->GetCollider()->CheckHitPolygon(actor2->GetTransform());
			if (result2 && result2->m_hitFlag)
			{
				actor2->OnHitPolygon(result2);
			}

			//�Փ˔���
			if (actor1->GetCollider()->CheckCollision(
				actor1->GetTransform(),
				actor2->GetTransform(), actor2->GetCollider()))
			{
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);
			}
		}
	}
}

#ifdef _DEBUG
void ModelActorCollision::Draw() const
{
	for (auto actor : m_actorList)
	{
		actor->GetCollider()->Draw(actor->GetTransform());
	}
}
#endif