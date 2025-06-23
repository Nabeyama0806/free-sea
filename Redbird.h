#pragma once
#include "CharacterBase.h"

class RedBird : public CharacterBase
{
public:
	//�R���X�g���N�^
	RedBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType, int playerIndex) :
		CharacterBase("Man/Man3.mv1", "Resource/Model/bullet_red.mv1", camera, stage, position, bulletType, playerIndex)
	{
	}
};