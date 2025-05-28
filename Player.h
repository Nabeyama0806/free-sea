#pragma once
#include "ModelActor.h"
#include "Model.h"
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

	static constexpr Vector3 SpawnOffset = Vector3(0, 0, 400);	//開始時の座標
	static constexpr Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);	//自身のサイズ
	static constexpr float Speed = 7.5f * Scale.y;	//自身のサイズに合せた移動速度
	static constexpr float DashSpeed = 1.4f;		//ダッシュ時の速度倍率
	static constexpr int AnimeAmount = 2;			//アニメーションの総数

	const char* AnimeFileName[static_cast<int>(Anime::Length)] =
	{
		"Man/Idle.mv1",		//待機
		"Man/Sprint.mv1"	//ダッシュ
	};

	Camera* m_camera;
	int m_map;

protected:
	virtual void Update() override;	//更新
	virtual void Draw() override;

public:
	//コンストラクタ
	Player(Camera* camera, int mapModelHundle);
};