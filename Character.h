#pragma once
#include "ModelActor.h"
#include "Bullet.h"
#include "BulletStatus.h" 
#include "InputSystem.h"
#include "Vector3.h"
#include "Vector2.h"

class SpriteActor;
class Camera;
class Stage;

class Character : public ModelActor
{
private:
	static constexpr int MaxHealth = 160;			//体力
	static constexpr float Scale = 3.0f;			//自身のサイズ
	static constexpr float Speed = 1.2f * Scale;	//自身のサイズに合せた移動速度
	static constexpr float Radius = 13.0f;			//衝突判定の半径
	static constexpr float FlashTime = 0.5f;		//点滅時間

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

	//キャラクターモデルのファイルパス
	const char* ModelFilePath[InputSystem::MaxPadAmount] =
	{
		"Man/Man.mv1",	//プレイヤー1
		"Man/Man4.mv1",	//プレイヤー2
		"Man/Man3.mv1",	//プレイヤー3
		"Man/Man2.mv1",	//プレイヤー4

	};

	//プレイヤー毎に表示する弾モデルのファイルパス
	const char* BulletModelFilePath[InputSystem::MaxPadAmount] =
	{
		"Resource/Model/bullet_blue.mv1",
		"Resource/Model/bullet_green.mv1",
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_pink.mv1",
	};

	const Vector2 HealthDrawPos[InputSystem::MaxPadAmount] =
	{
		Vector2(250, 140),
		Vector2(250, 290),
		Vector2(250, 440),
		Vector2(250, 590),
	};
 
protected:
	static constexpr Vector3 BulletOffset = Vector3(0, 50, 0);
	static constexpr int HealthSlideHeight = 40;

	SpriteActor* m_spriteActor;
	BulletStatus* m_bulletStatus;	//弾のステータス
	Camera* m_camera;
	Stage* m_stage;				
	Vector2 m_shotRotate;		//射出方向の回転
	Vector2 m_inputValue;		//入力値	

	//自身に関する変数
	int m_health;				//体力
	int m_playerIndex;			//自身のプレイヤー番号
	float m_flashTime;			//残りの点滅時間
	bool m_isGrounded;			//床との接触判定

	//弾の生成に必要な変数
	int m_bulletIndex;			//弾のインデックス
	int m_bulletInstanceAmount;	//生成された弾の数
	float m_shotElapsedTime;	//発射間隔の経過時間
	float m_bulletElapsedTime;	//弾間の経過時間
	int	m_bulletAmount;			//一回で発射される弾の数
	float m_shotCoolTime;		//発射間隔
	float m_shotRate;			//弾間の発射間隔
	bool m_isShot;				//発射中

	virtual void Update() override;	//更新
	virtual void Draw() override;	//描画

	virtual void BulletShot();		//弾の発射
	virtual bool CreateBullet();	//弾の生成

public:
	//コンストラクタ
	Character(
		Camera* camera,
		Stage* stage,
		const Vector3& position,
		int playerIndex,
		int bulletIndex
	);

	//被弾
	void Damage(int damage);

	//生存確認
	bool IsAlive() const
	{
		return m_health > 0;
	}

	//射出方向の取得
	const Vector3 GetShotForward()
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
};