#include "SceneGame.h"
#include "SceneResult.h"
#include "Screen.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Fade.h"
#include "Camera.h"
#include "Player.h"
#include "ImageLoader.h"
#include "ModelLoader.h"
#include "DxLib.h"

//初期化
void SceneGame::Initialize()
{
	//ルート
	m_rootNode = new Node();

	//メインカメラ
	m_mainCamera = new Camera();
	m_rootNode->AddChild(m_mainCamera);

	//背景
	m_map = new ModelActor("Ground", "Environment/Ground.mv1");
	m_mesh = new ModelActor("Mesh", "Environment/Ground_Mesh.mv1");
	MV1SetupCollInfo(m_mesh->GetModelHandle(), -1);
	m_rootNode->AddChild(m_map);
	m_rootNode->AddChild(m_mesh);

	//アクターレイヤー
	Node* actorLayer = new Node();
	m_rootNode->AddChild(actorLayer);

	//UIレイヤー
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//プレイヤー
	m_player = new Player(m_mainCamera, m_map->GetModelHandle());
	m_rootNode->AddChild(m_player);
	m_mainCamera->SetLookAt(m_player);

	//BGM

}

//終了
void SceneGame::Finalize()
{
	//ノードの削除
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;

	//BGM
	DeleteSoundMem(m_bgm);
}

//更新
SceneBase* SceneGame::Update()
{
	//ノードの更新
	m_rootNode->TreeUpdate();
	MV1RefreshCollInfo(m_map->GetModelHandle(), -1);

	return this;
}

//描画
void SceneGame::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();
}