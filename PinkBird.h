#pragma once
#include "CharacterBase.h"

class PinkBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 2;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 1.0f;			//発射間隔
	static constexpr float BulletFiringRate = 0.3f;		//弾間の発射間隔

	const char* BulletFilePath = "Resource/Model/Bullet.mv1";	//弾のモデルファイルパス

public:
	//コンストラクタ
	PinkBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType) :
		CharacterBase(BulletFilePath, "Man/Man2.mv1", camera, stage, position, bulletType)
	{
		//弾
		m_maxBulletAmount = BulletAmount;
		m_shotCoolTime = ShotCoolTime;
		m_bulletFiringRate = BulletFiringRate;
	}
};