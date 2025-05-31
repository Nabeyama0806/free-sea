#pragma once
#include "ModelActor.h"

class Player;

class Bullet : public ModelActor
{
public:
	static constexpr float Scale = 20.0f;		//大きさの調整

private:
	static constexpr float AddForce = 550.0f;	//投げる力
	static constexpr float EraseTime = 3.0f;	//生存時間

	Player* m_player;
	Vector3 m_forward;
	float m_elapsedTime;	//生成されてからの生存時間

	virtual void Update() override;		//更新
	Vector3 Shot(Vector3& position) const;

public:
	//コンストラクタ
	Bullet(const Vector3& position, const Vector3& forward, Player* player);
};