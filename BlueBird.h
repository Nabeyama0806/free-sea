#pragma once
#include "CharacterBase.h"

class BlueBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 5;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 1.7f;			//発射間隔
	static constexpr float BulletFiringRate = 0.24f;	//弾間の発射間隔

	void BulletShot();		//発射
	bool BulletInstance();	//弾の生成

protected:
	virtual void Update() override;			//更新

public:
	//コンストラクタ
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};