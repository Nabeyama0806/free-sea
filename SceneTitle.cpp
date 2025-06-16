#include "SceneTitle.h"
#include "SceneGame.h"
#include "CharacterBase.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
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
		//プレイヤーごとのキャラ選択
		for (int i = 0; i < GetJoypadNum(); ++i)
		{
			InputSystem::ActionMap actionMap = static_cast<InputSystem::ActionMap>(i);

			//キャラ選択
			if (InputSystem::GetInstance()->SelectLeft(actionMap))	m_select[i]--;
			if (InputSystem::GetInstance()->SelectRight(actionMap)) m_select[i]++;

			//範囲内に調整
			if (m_select[i] <= 0) m_select[i] = static_cast<int>(CharacterBase::Type::Length);
			if (m_select[i] >= static_cast<int>(CharacterBase::Type::Length)) m_select[i] = 0;

			//決定ボタンが押されたらゲーム開始
			if (InputSystem::GetInstance()->IsDecision(actionMap))
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