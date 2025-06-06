#pragma once
#include "ModelActor.h"
#include "Vector3.h"

class Camera;
class Stage;

class CharacterBase : public ModelActor
{
private:
	static constexpr float Scale = 3.0f;			//自身のサイズ
	static constexpr float Speed = 1.2f * Scale;	//自身のサイズに合せた移動速度
	static constexpr float Radius = 45.0f;			//衝突判定の半径
	static constexpr float InvincibleTime = 0.8f;	//無敵時間

	//アニメーションパターン
	enum class Anime
	{
		Idle,
		Run,

		Length,
	};

	//アニメーション配列
	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//待機
		"Man/Sprint.mv1"	//移動
	};

protected:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);

	const char* m_modelFilePath;
	Camera* m_camera;
	Stage* m_stage;
	int m_playerIndex;			//自身のプレイヤー番号
	float m_invincibleTime;		//残りの無敵時間
	bool m_isGrounded;			//床との接触判定
	bool m_isShot;				//発射中

	int m_bulletInstanceAmount;	//生成された弾の数
	float m_shotElapsedTime;	//発射間隔の経過時間
	float m_bulletElapsedTime;	//弾間の経過時間

	int m_health;				//体力
	int	m_maxBulletAmount;		//一回で発射される弾の数
	float m_shotCoolTime;		//発射間隔
	float m_bulletFiringRate;	//弾間の発射間隔

	virtual void Update() override;	//更新
	virtual void Draw() override;

public:
	//コンストラクタ
	CharacterBase(
		const char* modelFilepath,
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		int health,
		int playerIndex
	);

	//被弾
	void Damage(int damage);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) {};
};