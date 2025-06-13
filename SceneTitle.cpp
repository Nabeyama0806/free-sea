#include "SceneTitle.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "SceneGame.h"
#include "CharacterBase.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Input.h"
#include "DxLib.h"

//初期化
void SceneTitle::Initialize()
{
	//ノード
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title.png", Screen::Center));

	//接続されているパッド数を取得
	m_padAmount = GetJoypadNum();

	//接続されているパッドの数だけ配列の要素数を追加
	for (int i = 0; i < GetJoypadNum(); ++i)
	{
		m_select.push_back(i);
	}

	//BGM
	m_bgm = SoundManager::Load("Resource/sound/bgm_title.mp3");
	SoundManager::Play(m_bgm, DX_PLAYTYPE_LOOP);
}

//終了
void SceneTitle::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//更新
SceneBase* SceneTitle::Update()
{
	//いずれかのキーが押されたらゲームシーンへ移動
	switch (m_phase)
	{
	case SceneTitle::Phase::Home:
		if (Input::GetInstance()->IsAnyKeyDown())
		{
			m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title_select.png", Screen::Center));
			m_phase = Phase::Select;
		}
		break;

	case SceneTitle::Phase::Select:

		for (int i = 0; i < GetJoypadNum(); ++i)
		{
			//決定ボタンが押されたらゲーム開始
			if (InputSystem::GetInstance()->IsDecision(static_cast<InputSystem::ActionMap>(i)))
			{
				SoundManager::SoundStop(m_bgm);
				m_phase = Phase::GameStart;
			}
		}
		break;

	case SceneTitle::Phase::GameStart:
		return new SceneGame(m_select);
		break;

	default:
		break;
	}

	//ノードの更新
	m_rootNode->TreeUpdate();

	return this;
}

//描画
void SceneTitle::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();
}