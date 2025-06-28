#pragma once
#include "Transform.h"
#include "Screen.h"

//クラスの前方宣言
class SceneBase;
class Sprite;

//シーン遷移クラス
class SceneManager
{
private:
	//フェーズ
	enum class Phase
	{
		Run,		//実行中
		FadeOut,	//フェードアウト
		Loading,	//ロード中
		Transition,	//遷移
	};

	Phase m_phase;

private:
	SceneBase* m_scene;				//実行中のシーン
	SceneBase* m_nextScene;			//遷移先のシーン
	Sprite*	m_sprite;				//スプライト
	Transform m_transform;

public:
	//コンストラクタ
	SceneManager();

	//シングルトン
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}


	void Update();		//更新
	void Draw();		//描画	
	void Release();		//後処理

	//シーン切り替え
	void LoadScene(SceneBase* nextScene);
};