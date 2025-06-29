#pragma once
#include"SceneBase.h"
#include"Character.h"
#include "InputSystem.h"
#include "Vector3.h"
#include <list>
#include <vector>

//クラスの前方宣言
class Node;
class ModelActor;
class Sprite;
class Camera;
class Transform;
class Stage;

//ゲームシーン
class SceneGame : public SceneBase
{	
private:
	static constexpr float ResultTransitionTime = 2.0f;		//プレイヤーが死んでからリザルト画面に遷移するまでの時間

	//モデルの事前読み込み
	const std::list<const char*> ModelPreload =
	{
		"Man/Man.mv1",
		"Man/Man4.mv1",
		"Man/Man3.mv1",
		"Man/Man2.mv1",
	};


	//キャラクターアイコンのファイルパス
	const char* CharacterIconFilePath[InputSystem::MaxPadAmount] =
	{
		"Resource/Texture/status_icon_blue.png",
		"Resource/Texture/status_icon_green.png",
		"Resource/Texture/status_icon_red.png",
		"Resource/Texture/status_icon_pink.png",
	}; 

	//キャラクターアイコンの名前
	const char* CharacterIconName[InputSystem::MaxPadAmount] =
	{
		"blue_bird_icon",
		"green_bird_icon",
		"red_bird_icon",
		"pink_bird_icon",
	};

	//キャラクターアイコンの位置
	const Vector2 CharacterIconPosition[InputSystem::MaxPadAmount] =
	{
		Vector2(200, 150),
		Vector2(200, 300),
		Vector2(200, 450),
		Vector2(200, 600),
	};

	const Vector3 PlayerPosition[InputSystem::MaxPadAmount] =
	{
		Vector3(-620, 0, 0),
		Vector3(620, 0, 0),
		Vector3(0, 0, 450),
		Vector3(0, 0, -450),
	};

	Node* m_rootNode;
	Character* m_characters[InputSystem::MaxPadAmount];
	Camera* m_mainCamera;
	Stage* m_stage;
	Sprite* m_sprite;	//キャラクターアイコンの表示用
	Transform m_transform;

	Vector3 cameraPos = Vector3(0, 0, -700);
	std::vector<int> m_playerBullets;

	float m_resultTransitionTime;
	int m_padAmount;	
	int m_bgm;

	//最後のプレイヤーか判定
	void IsLastCharacter() const;

public:
	//コンストラクタ
	SceneGame(std::vector<int>& playerBullets, int padAmount) :
		m_padAmount(padAmount),
		m_rootNode(nullptr),
		m_stage(nullptr),
		m_mainCamera(nullptr),
		m_sprite(nullptr),
		m_characters{nullptr},
		m_resultTransitionTime(ResultTransitionTime),
		m_playerBullets(playerBullets),
		m_bgm(0)
	{
	}

	virtual void Preload() override;		//事前読み込み
	virtual void Initialize() override;		//初期化
	virtual void Finalize() override;		//終了
	virtual void Update() override;			//更新
	virtual void Draw() override;			//描画
};