#pragma once
#include "CharacterBase.h"

class PinkBird : public CharacterBase
{
public:
	//コンストラクタ
	PinkBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType, int playerIndex) :
		CharacterBase("Man/Man2.mv1", "Resource/Model/bullet_pink.mv1", camera, stage, position, bulletType, playerIndex)
	{
	}
};