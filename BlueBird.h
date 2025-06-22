#pragma once
#include "CharacterBase.h"
#include "Bullet.h"

class BlueBird : public CharacterBase
{
private:
	static constexpr int BulletAmount = 2;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 0.8f;			//発射間隔
	static constexpr float BulletFiringRate = 0.2f;		//弾間の発射間隔

	const char* BulletFilePath = "Resource/Model/Bullet.mv1";	//弾のモデルファイルパス

public:
	//コンストラクタ
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, Bullet::Type bulletType) :
		CharacterBase("Man/Man.mv1", BulletFilePath, camera, stage, position, bulletType)
	{
		//弾
		m_maxBulletAmount = BulletAmount;
		m_shotCoolTime = ShotCoolTime;
		m_bulletFiringRate = BulletFiringRate;
	}
};