#include "SceneGame.h"
#include "SceneResult.h"
#include "SoundLoader.h"
#include "SoundManager.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Camera.h"
#include "Player.h"
#include "Stage.h"
#include "DxLib.h"

//初期化
void SceneGame::Initialize()
{
	//グローバルライト
	SetGlobalAmbientLight(GetColorF(1, 1, 1, 0));

	//ルート
	m_rootNode = new Node();

	//メインカメラ
	m_mainCamera = new Camera();
	m_rootNode->AddChild(m_mainCamera);

	//アクターレイヤー
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//スカイボックス
	ModelActor* skybox = new ModelActor("Skybox", "Resource/Model/Skybox.mv1");
	skybox->ChangeScale(10000);
	actorLayer->AddChild(skybox);

	//ステージ
	m_stage = new Stage();
	MV1SetupCollInfo(m_stage->GetModelHandle(), m_stage->GetFrameIndex());
	m_rootNode->AddChild(m_stage);
	m_mainCamera->SetLookAt(m_stage);

	//UIレイヤー
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//プレイヤー
	for (int i = 0; i < 2; ++i)
	{
		m_player[i] = new Player(m_mainCamera, m_stage, PlayerPosition[i], i);
		actorLayer->AddChild(m_player[i]);
	}
	
	//BGM
	m_bgm = SoundLoader::GetInstance()->Load("Resource/Sound/bgm_game.mp3");
	SoundManager::Play(m_bgm, DX_PLAYTYPE_LOOP);
}

//終了
void SceneGame::Finalize()
{
	//ノードの削除
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;

	//BGM
	SoundLoader::GetInstance()->Delete("Resource/Sound/bgm_game.mp3");
}

//更新
SceneBase* SceneGame::Update()
{
	//ノードの更新
	m_rootNode->TreeUpdate();

	return this;
}

//描画
void SceneGame::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();
}