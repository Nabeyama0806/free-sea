#pragma once
#include "CharacterBase.h"
#include "Bullet.h"
#include "ReflectionBullet.h"
#include "StraightBullet.h"
#include "DiffusionBullet.h"

class BlueBird : public CharacterBase
{
public:
	//コンストラクタ
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType, int playerIndex) :
		CharacterBase("Man/Man.mv1", "Resource/Model/bullet_blue.mv1", camera, stage, position, bulletType, playerIndex)
	{
	}
};