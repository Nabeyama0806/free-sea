#pragma once
#include "ModelActor.h"
#include "Model.h"
#include "Stage.h"
#include "Vector3.h"
#include "Camera.h"
#include <vector>

class Camera;

class Player : public ModelActor
{
private:
	enum class Anime
	{
		Idle,
		Run,

		Length,
	};
	
	static constexpr Vector3 SpawnPos = Vector3(0, 0, 0);		//開始時の座標
	static constexpr Vector3 BulletPosOffset = Vector3(0, 50, 0);
	static constexpr float Scale = 3.0f;			//自身のサイズ
	static constexpr float Speed = 1.2f * Scale;	//自身のサイズに合せた移動速度
	static constexpr float Radius = 20.0f;			//衝突判定の半径

	//弾
	static constexpr int BulletAmount = 3;				//一回で発射される弾の数
	static constexpr float ShotCoolTime = 1.4f;			//発射間隔
	static constexpr float BulletFiringRate = 0.27f;	//弾間の発射間隔

	//アニメーション配列
	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//待機
		"Man/Sprint.mv1"	//移動
	};

	Camera* m_camera;
	Stage* m_stage;
	int m_playerIndex;			//自身のプレイヤー番号
	int m_bulletInstanceAmount;	//生成された弾の数
	float m_shotElapsedTime;	//発射間隔の経過時間
	float m_bulletElapsedTime;	//弾間の経過時間
	bool m_isGrounded;			//床との接触判定
	bool m_isShot;				//発射中

	void Move(Anime& anime);		//移動
	void BulletShot();				//発射
	bool BulletInstance();			//弾の生成

protected:
	virtual void Update() override;	//更新
	virtual void Draw() override;

public:
	//コンストラクタ
	Player(Camera* camera, Stage* stage, int playerIndex);

	//衝突イベント
	virtual void OnCollision(const ModelActor* other);
};