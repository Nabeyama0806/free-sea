#include "SceneManager.h"
#include "SceneBase.h"
#include "Sprite.h"
#include "Fade.h"
#include "DxLib.h"

//コンストラクタ
SceneManager::SceneManager() :
	m_scene(nullptr),
	m_nextScene(nullptr),
	m_sprite(nullptr),
	m_phase(Phase::Loading)
{
	//姿勢情報
	m_transform.position = Screen::Center;

	//スプライトの読み込み
	m_sprite = new Sprite();
	m_sprite->Register("Resource/Texture/loading.png");
	m_sprite->Load();
}

//後処理
void SceneManager::Release()
{
	//実行中のシーンと遷移先のシーンが同じなら、多重deleteしない
	if (m_scene == m_nextScene)
	{
		m_nextScene = nullptr;
	}

	//実行中のシーンの破棄
	if (m_scene != nullptr)
	{
		m_scene->Finalize();
		delete m_scene;
		m_scene = nullptr;
	}

	//遷移先シーンの破棄
	if (m_nextScene != nullptr)
	{
		m_nextScene->Finalize();
		delete m_nextScene;
		m_nextScene = nullptr;
	}
}

//更新
void SceneManager::Update()
{
	switch (m_phase)
	{
		//実行中
	case Phase::Run:
		//実行中のシーンの更新
		m_scene->Update();

		//遷移先のシーンが実行中のシーンと異なる場合に遷移する
		if (m_nextScene != m_scene)
		{
			//フェードアウト開始
			m_phase = Phase::FadeOut;
			Fade::GetInstance()->StartFadeOut();
		}
		break;

		//フェードアウト
	case Phase::FadeOut:
		//フェードアウトが終わるまで待機
		if (Fade::GetInstance()->IsFade()) break;

		//フェードが終わったのでシーン遷移する
		m_phase = Phase::Loading;
		break;

	case Phase::Loading:
		//非同期ロードの開始
		SetUseASyncLoadFlag(TRUE);
		m_nextScene->Preload();

		//非同期ロードを終了してからシーン遷移
		if (GetASyncLoadNum() == 0)
		{
			SetUseASyncLoadFlag(FALSE);
			m_phase = Phase::Transition;
		}
		else
		{
			//ロード中のスプライトを更新
			m_sprite->Update();
		}
		break;

		//シーン遷移
	case Phase::Transition:

		//実行中のシーンがあれば破棄する
		if (m_scene)
		{
			m_scene->Finalize();
			delete m_scene;
			m_scene = nullptr;
		}

		//遷移先のシーンを実行中のシーンにする
		m_scene = m_nextScene;
		m_scene->Initialize();

		//フェードイン
		Fade::GetInstance()->StartFadeIn(0.2f);

		m_phase = Phase::Run;
		break;
	}
}

//描画
void SceneManager::Draw()
{
	switch (m_phase)
	{
	case Phase::Run:
	case Phase::FadeOut:
		if (m_scene) m_scene->Draw();
		break;

	case Phase::Loading:
		m_sprite->Draw(m_transform); //ロード中のスプライトを描画
		break;
	}
}

//シーン切り替え
void SceneManager::LoadScene(SceneBase* nextScene)
{
	m_nextScene = nextScene;
}