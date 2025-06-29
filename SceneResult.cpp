#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "Screen.h"
#include "Time.h"

//初期化
void SceneResult::Initialize()
{
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new SpriteActor("Result", "Resource/Texture/result.png", Screen::Center));

	//効果音の再生
	SoundManager::Play("Resource/Sound/se_winner.mp3");

	//姿勢情報
	m_transform.position = Screen::Center;

	//画像の読み込み
	m_sprite = new Sprite();
	m_sprite->Register(TextureName[m_playerIndex], SpriteAnimation(TextureFilePath[m_playerIndex]));
	m_sprite->Load();
	m_sprite->Play(TextureName[m_playerIndex]);
}

//終了処理
void SceneResult::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//更新
void SceneResult::Update()
{
	//ノードの更新
	m_rootNode->TreeUpdate();

	//画像の更新
	m_sprite->Update();

	if (m_waitTransitionTime > 0)
	{
		m_waitTransitionTime -= Time::GetInstance()->GetDeltaTime();
	}

	//いずれかのキーが押されたらタイトル画面に遷移
	if (m_waitTransitionTime <= 0 && InputSystem::GetInstance()->IsAnyKeyDown())
	{
		SceneManager::GetInstance()->LoadScene(new SceneTitle());
	}
}

//描画
void SceneResult::Draw()
{
	//ノードの更新
	m_rootNode->TreeDraw();

	//画像の表示
	m_sprite->Draw(m_transform);
}