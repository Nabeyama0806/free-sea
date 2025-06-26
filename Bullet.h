#pragma once
#include "ModelActor.h"
#include "Stage.h"
#include <string>

class BulletStatus;

class Bullet : public ModelActor
{
private:
	static constexpr float Size = 0.1f; //弾の大きさ

	Stage* m_stage;	
	Vector3 m_forward;	
	float m_elapsedTime;

	//弾のステータス
	BulletStatus* m_bulletStatus;

	int m_reflectAmount;		//反射可能回数
	float m_addForce;			//投げる力
	int m_power;				//攻撃力
	float m_aliveTime;			//生存時間(秒)
	float m_size;				//大きさ

protected:
	virtual void Update() override;		//更新

public:
	// コンストラクタ
	Bullet(
		const char* filePath,
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		int bulletIndex
	);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other);
};