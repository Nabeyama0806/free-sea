#pragma once
#include "PlayerBase.h"

class Player : public PlayerBase
{
private:
	//弾
	static constexpr int BulletAmount = 3;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 1.4f;			//発射間隔
	static constexpr float BulletFiringRate = 0.27f;	//弾間の発射間隔

public:
	//コンストラクタ
	Player(Camera* camera, Stage* stage, const Vector3& position, PlayerBase::Bullet bullet, int playerIndex);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other);
};