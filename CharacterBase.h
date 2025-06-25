#pragma once
#include "ModelActor.h"
#include "Bullet.h"
#include "Vector3.h"
#include "Vector2.h"
 
class SpriteActor;
class Camera;
class Stage;

class CharacterBase : public ModelActor
{
private:
	static constexpr int MaxPlayerAmount = 4;

	static constexpr int MaxHealth = 160;			//体力
	static constexpr float Scale = 3.0f;			//自身のサイズ
	static constexpr float Speed = 1.2f * Scale;	//自身のサイズに合せた移動速度
	static constexpr float Radius = 20.0f;			//衝突判定の半径
	static constexpr float FlashTime = 0.8f;		//点滅時間

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
		"Man/Walking.mv1"	//移動
	};

	const Vector2 HealthDrawPos[MaxPlayerAmount] =
	{
		Vector2(250, 140),
		Vector2(250, 290),
		Vector2(250, 440),
		Vector2(250, 590),
	};
 
protected:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);
	static constexpr int HealthSlideHeight = 40;

	const char* BulletFilePath;

	SpriteActor* m_spriteActor;
	Camera* m_camera;
	Stage* m_stage;				
	Vector2 m_shotRotate;		//射出方向の回転
	Vector2 m_inputValue;		//入力値	
	Bullet::Type m_bulletType;	//弾の種類

	//自身に関する変数
	int m_maxHealth;			//最大体力
	int m_health;				//体力
	int m_playerIndex;			//自身のプレイヤー番号
	float m_flashTime;			//残りの点滅時間
	bool m_isGrounded;			//床との接触判定

	//弾の生成に必要な変数
	int m_bulletInstanceAmount;	//生成された弾の数
	float m_shotElapsedTime;	//発射間隔の経過時間
	float m_bulletElapsedTime;	//弾間の経過時間
	int	m_maxBulletAmount;		//一回で発射される弾の数
	float m_shotCoolTime;		//発射間隔
	float m_bulletFiringRate;	//弾間の発射間隔
	bool m_isShot;				//発射中

	virtual void Update() override;	//更新
	virtual void Draw() override;	//描画

	virtual void BulletShot();		//弾の発射
	virtual bool CreateBullet();	//弾の生成

public:
	//コンストラクタ
	CharacterBase(
		const char* modelFilepath,
		const char* bulletFilePath,
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		Bullet::Type bulletType,
		int playerIndex
	);

	//被弾
	void Damage(int damage);

	//射出方向の取得
	Vector3 GetShotForward()
	{
		float length = 80.0f;	//射出方向の長さ
		Vector3 tmp = Vector3(m_shotRotate.x, 0, m_shotRotate.y);
		if (!tmp.IsZero()) m_shotRotate.Normalize();
		else
		{
			Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
			m_shotRotate = forward;
			tmp = forward;
		}
		return tmp;
	}

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) {};
};