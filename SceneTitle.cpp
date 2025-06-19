#include "SceneTitle.h"
#include "SceneGame.h"
#include "CharacterBase.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Input.h"
#include "Debug.h"
#include "DxLib.h"

//初期化
void SceneTitle::Initialize()
{
	m_transform.position = Screen::Center;
	m_transform.scale = 0.2f;

	//ノード
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title.png", Screen::Center));

	//接続されているパッド数を取得
	m_padAmount = GetJoypadNum();

	//接続されているパッドの数だけ配列の要素数を追加
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_select.push_back(0);
	}

	//画像の読み込み
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i] = new Sprite();
		m_sprites[i]->gridSize = Vector2(1920, 1032);
		for (int j = 0; j < static_cast<int>(CharacterBase::Type::Length); ++j)
		{
			m_sprites[i]->Register(TextureName[j], SpriteAnimation(CharacterImage[j]));
			m_sprites[i]->Load();
		}
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
	//ノードの更新
	m_rootNode->TreeUpdate();

	//画像の表示
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i]->Update();
	}
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i]->Play(TextureName[m_select[i]]);
	}

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
		for (int i = 0; i < m_padAmount; ++i)
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

	return this;
}

//描画
void SceneTitle::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();

	//ホーム画面では何も描画しない
	if (m_phase == SceneTitle::Phase::Home) return; 

	//画像の描画
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_transform.position = Screen::Center + DrawPosOffset[i];
		m_sprites[i]->Draw(m_transform);
	}
}