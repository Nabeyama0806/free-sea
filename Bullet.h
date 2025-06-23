#pragma once
#include "ModelActor.h"
#include "DxLib.h"

class Stage;

class Bullet : public ModelActor
{
public:
	enum class Type
	{
		Reflection,		//反射弾
		Straight,		//直進弾
		Diffusion,		//拡散弾

		Length,		
	};

	int m_health;				//反射できる回数
	int m_power;				//攻撃力
	float m_addForce;			//投げる力
	float m_elapsedTime;		//生成されてからの生存時間
	float m_size;				//大きさの調整
	float m_eraseTime;			//生存時間(秒)

private:
	static constexpr int MaxHealth = 3;
	static constexpr int Power = 15;
	static constexpr float AddForce = 500.0f;
	static constexpr float Size = 2.0f;	
	static constexpr float EraseTime = 2.0f;	

	Stage* m_stage;
	Vector3 m_forward;		//自身の正面ベクトル

	virtual void Update() override;		//更新

public:
	//コンストラクタ
	Bullet(
		const char* filePath,
		const Vector3& position,
		const Vector3& forward,
		Stage* stage,
		const float size = Size
	);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other);
};