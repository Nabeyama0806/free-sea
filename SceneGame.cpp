#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "SpriteLoader.h"
#include "ModelLoader.h"
#include "Bullet.h"
#include "Character.h"
#include "Input.h"
#include "Node.h"
#include "Time.h"
#include "Transform.h"
#include "Camera.h"
#include "Stage.h"
#include "DxLib.h"

//事前読み込み
void SceneGame::Preload()
{
	//画像のプリロード
	for (const char* modelPath : CharacterIconFilePath)
	{
		SpriteLoader::GetInstance()->Load(modelPath);
	}

	//モデルのプリロード
	for (const char* modelPath : ModelPreload)
	{
		ModelLoader::GetInstance()->Load(modelPath);
	}
}

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

	//ステージ
	m_stage = new Stage();
	MV1SetupCollInfo(m_stage->GetModelHandle(), m_stage->GetFrameIndex());
	actorLayer->AddChild(m_stage);
	m_mainCamera->SetLookAt(m_stage);

	//UIレイヤー
	Node* uiLayer = new Node();
	m_rootNode->AddChild(uiLayer);

	//生成するキャラの分岐
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_characters[i] = new Character(m_mainCamera, m_stage, PlayerPosition[i], i, m_playerBullets[i]);
		actorLayer->AddChild(m_characters[i]);
	}

	//キャラクターアイコンの読み込み
	m_sprite = new Sprite();
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprite->Register(CharacterIconName[i], SpriteAnimation(CharacterIconFilePath[i]));
		m_sprite->Load();
	}
	m_transform.scale = 0.6f;
	
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
	SoundManager::SoundStop(m_bgm);
}

//更新
void SceneGame::Update()
{
	//キャラクターが残り1人ならリザルトへ遷移
	IsLastCharacter();

	//ノードの更新
	m_rootNode->TreeUpdate();
	m_sprite->Update();
}

//描画
void SceneGame::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();

	//キャラクターアイコンの描画
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_transform.position = CharacterIconPosition[i];
		m_sprite->Play(CharacterIconName[i]);
		m_sprite->Draw(m_transform);
	}
}

//最後のキャラクターかどうかを判定
void SceneGame::IsLastCharacter() const 
{
	//キャラクターの生存数をカウント
	Character* lastCharacter = nullptr;
	int aliveCount = 0;
	for (const auto& character : m_characters) 
	{ 
		//キャラクターが存在しない場合はスキップ
		if (!character) continue;

		//最後の生存キャラクター候補を保存
		if (character->IsAlive())
		{
			lastCharacter = character;
			aliveCount++;
		}

		//2人以上生存
		if (aliveCount >= 2) return;
	}
	
	//生存キャラクターが1人ならリザルトへ遷移
	if (aliveCount == 1) SceneManager:: GetInstance()->LoadScene(new SceneResult(lastCharacter));
}
