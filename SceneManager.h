#pragma once

//クラスの前方宣言
class SceneBase;

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

private:
	SceneBase* m_scene;				//実行中のシーン
	SceneBase* m_nextScene;			//遷移先のシーン
	Phase m_phase;					//フェーズ

public:
	//コンストラクタ
	SceneManager() :
		m_scene(nullptr),
		m_nextScene(nullptr),
		m_phase(Phase::Loading) {
	}

	//シングルトン
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}


	void Updeta();		//更新
	void Draw();		//描画	
	void Release();		//後処理

	//シーン切り替え
	void LoadScene(SceneBase* nextScene);
};