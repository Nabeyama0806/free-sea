#pragma once
#include "ModelActor.h"
#include "CharacterBase.h"
#include "DxLib.h"

class Stage;

class Bullet : public ModelActor
{
private:
	static constexpr float Scale = 25.0f;		//大きさの調整
	static constexpr float EraseTime = 2.5f;	//生存時間

	Stage* m_stage;
	Vector3 m_forward;		//自身の正面ベクトル

	int m_health;			//反射できる回数
	int m_power;			//攻撃力
	float m_addForce;		//投げる力
	float m_elapsedTime;	//生成されてからの生存時間

	virtual void Update() override;		//更新

public:
	//コンストラクタ
	Bullet(
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		int maxHelath,
		int power,
		float addForce,
		float Size = 30
	);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) 
	{
		if (other->GetName() == "Player")
		{
			//自分の親ならダメージを与えない
			if (GetParent() == other) return;
			
			//他プレイヤーと衝突したらダメージを与える
			dynamic_cast<CharacterBase*>(const_cast<ModelActor*>(other))->Damage(m_power);
			Destroy();
		}
	}
};