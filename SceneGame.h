#pragma once
#include"SceneBase.h"
#include "Vector3.h"
#include <list>

//クラスの前方宣言
class Node;
class ModelActor;
class Camera;
class Stage;
class BlueBird;
class GreenBird;

//	ゲームシーン
class SceneGame : public SceneBase
{
private:
	static constexpr float ResultTransitionTime = 2.0f;	//プレイヤーが死んでからリザルト画面に遷移するまでの時間

	const std::list<const char*> ImagePreload =
	{
		//"title.png"
	};

	const Vector3 PlayerPosition[2] =
	{
		Vector3(650, 0, 0),
		Vector3(-650, 0, 0),
	};

	Node* m_rootNode;
	GreenBird* m_greenBird;
	BlueBird* m_blueBird;
	Camera* m_mainCamera;
	Stage* m_stage;

	Vector3 cameraPos = Vector3(0, 0, -700);

	float m_resultTransitionTime;
	int m_playerIndex;
	int m_bgm;

public:
	//コンストラクタ
	SceneGame() :
		m_rootNode(nullptr),
		m_stage(nullptr),
		m_greenBird(nullptr),
		m_blueBird(nullptr),
		m_mainCamera(nullptr),
		m_resultTransitionTime(ResultTransitionTime),
		m_playerIndex(0),
		m_bgm(0)
	{
	}

	virtual void Initialize() override;		//初期化
	virtual void Finalize() override;		//終了
	virtual SceneBase* Update() override;	//更新
	virtual void Draw() override;			//描画
};