#pragma once
#include"SceneBase.h"
#include"CharacterBase.h"
#include "ModelLoader.h"
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
	static constexpr int MaxControllerNum = 4;
	static constexpr float ResultTransitionTime = 2.0f;		//プレイヤーが死んでからリザルト画面に遷移するまでの時間

	//キャラクターアイコンのファイルパス
	const char* CharacterIconFilePath[MaxControllerNum] =
	{
		"Resource/Texture/status_icon_blue.png",
		"Resource/Texture/status_icon_green.png",
		"Resource/Texture/status_icon_red.png",
		"Resource/Texture/status_icon_pink.png",
	};

	//キャラクターアイコンの名前
	const char* CharacterIconName[MaxControllerNum] =
	{
		"blue_bird_icon",
		"green_bird_icon",
		"red_bird_icon",
		"pink_bird_icon",
	};

	//キャラクターアイコンの位置
	const Vector2 CharacterIconPosition[MaxControllerNum] =
	{
		Vector2(200, 150),
		Vector2(200, 300),
		Vector2(200, 450),
		Vector2(200, 600),
	};

	const Vector3 PlayerPosition[MaxControllerNum] =
	{
		Vector3(-620, 0, 0),
		Vector3(620, 0, 0),
		Vector3(0, 0, 450),
		Vector3(0, 0, -450),
	};

	Node* m_rootNode;
	CharacterBase* m_characters[MaxControllerNum];
	Camera* m_mainCamera;
	Stage* m_stage;
	Sprite* m_sprite;	//キャラクターアイコンの表示用
	Transform m_transform;

	Vector3 cameraPos = Vector3(0, 0, -700);
	std::vector<int> m_playerBullets;

	float m_resultTransitionTime;
	int m_bgm;

public:
	//コンストラクタ
	SceneGame(std::vector<int>& playerBullets) :
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

	virtual void Initialize() override;		//初期化
	virtual void Finalize() override;		//終了
	virtual SceneBase* Update() override;	//更新
	virtual void Draw() override;			//描画
};