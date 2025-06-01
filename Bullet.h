#pragma once
#include "ModelActor.h"

class Player;

class Bullet : public ModelActor
{
public:
	static constexpr int MaxHealth = 3;			//反射できる回数(体力)
	static constexpr float Scale = 20.0f;		//大きさの調整

private:
	static constexpr float AddForce = 550.0f;	//投げる力
	static constexpr float EraseTime = 3.0f;	//生存時間

	Player* m_player;		//プレイヤー
	Vector3 m_forward;		//自身の正面ベクトル
	int m_health;			//現在の体力
	float m_elapsedTime;	//生成されてからの生存時間

	virtual void Update() override;			//更新

public:
	//コンストラクタ
	Bullet(const Vector3& position, const Vector3& forward, Player* player);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other);
	virtual void OnHitPolygon(const ColliderResult* result);
};