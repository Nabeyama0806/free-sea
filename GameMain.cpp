#include "GameMain.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "GameConfig.h"
#include "Screen.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "ModelActorCollision.h"
#include "BulletData.h"
#include "Input.h"
#include "Time.h"
#include "Fade.h"
#include "Debug.h"
#include "DxLib.h"

//デストラクタ
GameMain::~GameMain()
{
	//自作スクリーンの破棄
	DeleteGraph(m_screen);

	//デバッグコンソールの終了
	Debug::Finalize();

	// Effekseer 終了
	Effkseer_End();

	// DxLib 終了
	DxLib_End();
}

//メインループ
void GameMain::Run()
{
	SetMainWindowText(GameConfig::Title); //ウィンドウタイトル
	SetAlwaysRunFlag(GameConfig::AlwayRunFlag); //非アクティブ時に動作する
	ChangeWindowMode(GameConfig::WindowMode); //ウィンドウモードで起動
	SetGraphMode(Screen::Width, Screen::Height, GameConfig::ColorBit); //ウィンドウサイズ
	SetBackgroundColor(0, 0, 0);

	//DXライブラリの初期化
	if (DxLib_Init())
	{
		throw - 1;
	}

	//エフェクト
	EffectManager::GetInstance()->Initialize();

	//シーン起動
	SceneManager::GetInstance()->LoadScene(new SceneTitle());

	//スクリーンの作成
	m_screen = MakeScreen(Screen::Width, Screen::Height);

	//弾データの読み込み
	BulletData::GetInstance()->LoadCSV();

	//ゲームループ
	while (ProcessMessage() == 0)
	{
		//入力システムの更新
		Input::GetInstance()->Update();

		//時間の更新
		Time::GetInstance()->Update();

		//ESCキーが押されたら終了
		if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE))
		{
			if (Input::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE))
			{
				break;
			}
		}

		//デバッグコンソールの初期化
		Debug::Initialize();

		//シーンの更新
		SceneManager::GetInstance()->Updeta();

		//衝突判定
		ModelActorCollision::GetInstance()->Update();

		//自作スクリーンに描画
		SetDrawScreen(m_screen);

		//画面に描かれているものを全て消す
		ClearDrawScreen();

		//シーンの描画
		SceneManager::GetInstance()->Draw();

		//エフェクトの更新
		EffectManager::GetInstance()->Update();

		//エフェクトの描画
		EffectManager::GetInstance()->Draw();

		//フェード
		Fade::GetInstance()->Update(m_screen);

		//自作スクリーンを裏画面に描画
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, m_screen, false);

		//裏画面と表画面をひっくり返す
		ScreenFlip();
	}

	//シーンの破棄
	SceneManager::GetInstance()->Release();
}