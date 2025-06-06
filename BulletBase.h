#pragma once
#include "ModelActor.h"

class Stage;

class BulletBase : public ModelActor
{
private:
	static constexpr float Scale = 25.0f;		//大きさの調整
	static constexpr float EraseTime = 3.0f;	//生存時間

	Stage* m_stage;
	Vector3 m_forward;		//自身の正面ベクトル

	int m_maxHealth;		//反射できる回数(体力)
	int m_health;			//現在の体力
	float m_addForce;		//投げる力
	float m_elapsedTime;	//生成されてからの生存時間

	virtual void Update() override;		//更新

public:
	//コンストラクタ
	BulletBase(
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		int maxHelath,
		float addForce
	);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) {};
};