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
class Camera;
class Stage;

//ゲームシーン
class SceneGame : public SceneBase
{	
private:
	static constexpr int MaxControllerNum = 4;
	static constexpr float ResultTransitionTime = 2.0f;		//プレイヤーが死んでからリザルト画面に遷移するまでの時間

	const std::list<const char*> ModelPreload =
	{
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_green.mv1",
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_pink.mv1",
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
		m_characters{nullptr},
		m_resultTransitionTime(ResultTransitionTime),
		m_playerBullets(playerBullets),
		m_bgm(0)
	{
		//モデルのプリロード
		/*for (const char* modelPath : ModelPreload)
		{
			ModelLoader::GetInstance()->Load(modelPath);
		}*/
	}

	virtual void Initialize() override;		//初期化
	virtual void Finalize() override;		//終了
	virtual SceneBase* Update() override;	//更新
	virtual void Draw() override;			//描画
};