#include "SceneGame.h"
#include "SceneResult.h"
#include "SoundManager.h"
#include "CharacterBase.h"
#include "BlueBird.h"
#include "GreenBird.h"
#include "RedBird.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Camera.h"
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
	actorLayer->AddChild(m_stage);
	m_mainCamera->SetLookAt(m_stage);

	//UIレイヤー
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//プレイヤーが選択したキャラ番号に応じて生成するキャラを変更
	for (int i = 0; i < GetJoypadNum(); ++i)
	{
		CharacterBase::Type chara = static_cast<CharacterBase::Type>(m_playerChara[i]);

		switch (chara)
		{
		case CharacterBase::Type::BlueBird:
			m_characters[i] = new BlueBird(m_mainCamera, m_stage, PlayerPosition[i], i);
			break;

		case CharacterBase::Type::GreenBird:
			m_characters[i] = new GreenBird(m_mainCamera, m_stage, PlayerPosition[i], i);
			break;

		case CharacterBase::Type::RedBird:
			m_characters[i] = new RedBird(m_mainCamera, m_stage, PlayerPosition[i], i);
			
		default:
			break;
		}
		actorLayer->AddChild(m_characters[i]);
	}
	
	//BGM
	m_bgm = SoundManager::Load("Resource/Sound/bgm_game.mp3");
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
	//SoundLoader::GetInstance()->Delete("Resource/Sound/bgm_game.mp3");
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