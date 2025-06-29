#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "BulletData.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Debug.h"
#include "DxLib.h"

//事前読み込み
void SceneTitle::Preload()
{
	//モデルのプリロード
	for (const char* modelPath : ModelPreload)
	{
		ModelLoader::GetInstance()->Load(modelPath);
	}
}

//初期化
void SceneTitle::Initialize()
{
	//姿勢情報
	m_transform.position = Screen::Center;
	m_transform.scale = 0.33f;

	//ノード
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title.png", Screen::Center));

	//タイトルロゴ
	m_rootNode->AddChild(new SpriteActor("TitleLogo", "Resource/Texture/title_logo.png", Screen::Center));

	//接続されているパッドの数だけ配列の要素数を追加
	for (int i = 0; i < InputSystem::GetInstance()->GetPadAmount(); ++i)
	{
		m_select.push_back(0);
	}

	//画像の読み込み
	for (int i = 0; i < InputSystem::MaxPadAmount; ++i)
	{
		m_sprites[i] = new Sprite();
		m_sprites[i]->gridSize = Vector2(1080, 1080);
		for (int j = 0; j < BulletData::GetInstance()->GetBulletListSize(); ++j)
		{
			//弾のデータにある名前とファイルパスを参照させる
			m_sprites[i]->Register(TextureName[j], SpriteAnimation(BulletImage[j]));
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
void SceneTitle::Update()
{
	//ノードの更新
	m_rootNode->TreeUpdate();

	//パッドの接続数を更新
	m_padAmount = InputSystem::GetInstance()->GetPadAmount();

	//いずれかのキーが押されたらゲームシーンへ移動
	switch (m_phase)
	{
	case SceneTitle::Phase::Home:
		if (InputSystem::GetInstance()->IsAnyKeyDown())
		{
			SoundManager::Play("Resource/Sound/se_next.mp3");
			m_rootNode->AddChild(new SpriteActor("Title", "Resource/Texture/title_select.png", Screen::Center));
			m_phase = Phase::Select;
		}
		break;

	case SceneTitle::Phase::Select:
		//各プレイヤーの弾選択
		for (int i = 0; i < m_padAmount; ++i)
		{
			//パッドの接続数が増えていれば追加
			if (i >= m_select.size()) m_select.push_back(0);

			InputSystem::ActionMap actionMap = static_cast<InputSystem::ActionMap>(i);
			if (InputSystem::GetInstance()->SelectLeft(actionMap))
			{
				m_select[i]--;
				SoundManager::Play("Resource/Sound/se_next.mp3");
			}

			if (InputSystem::GetInstance()->SelectRight(actionMap))
			{
				m_select[i]++;
				SoundManager::Play("Resource/Sound/se_next.mp3");
			}

			//範囲内に調整
			if (m_select[i] < 0) m_select[i] = BulletData::GetInstance()->GetBulletListSize() - 1;
			if (m_select[i] > BulletData::GetInstance()->GetBulletListSize() - 1) m_select[i] = 0;

			//決定ボタンが押されたらゲーム開始
			if (InputSystem::GetInstance()->IsDecision(actionMap))
			{
				SoundManager::SoundStop(m_bgm);
				SceneManager::GetInstance()->LoadScene(new SceneGame(m_select));
			}
		}
		break;
	}

	//ホーム画面では表示しない
	if (m_phase == SceneTitle::Phase::Home) return;

	//画像の更新
	for (int i = 0; i < m_padAmount; ++i)
	{
		m_sprites[i]->Update();
		m_sprites[i]->Play(TextureName[m_select[i]]);
	}
}

//描画
void SceneTitle::Draw()
{
	//ノードの描画
	m_rootNode->TreeDraw();

	//ホーム画面では描画しない	
	if (m_phase == SceneTitle::Phase::Home) return; 

	//画像の描画
	for (int i = 0; i < m_padAmount; ++i)
	{
		//画像の描画
		m_transform.position = Screen::Center + DrawPosOffset[i];
		m_sprites[i]->Draw(m_transform);
	}
}