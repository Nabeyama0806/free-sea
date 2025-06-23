#pragma once
#include "CharacterBase.h"

class GreenBird : public CharacterBase
{
public:
	//コンストラクタ
	GreenBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType, int playerIndex) :
		CharacterBase("Man/Man4.mv1", "Resource/Model/bullet_green.mv1", camera, stage, position, bulletType, playerIndex)
	{
	}
};