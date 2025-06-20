#pragma once
#include <vector>

class ModelAnimation;
class Transform;

class Model
{
private:
	const char* m_modelFileName;			//モデルのファイルパス

	std::vector<ModelAnimation*> m_animeList;	//アニメーション配列
	ModelAnimation* m_prevAnime;				//以前のアニメ
	ModelAnimation* m_nowAnime;					//現在のアニメ


	float m_elapsedTime;					//経過時間(秒)
	int m_modelHandle;						//モデルのID

public:
	//コンストラクタ
	Model(const char* modelFileName, bool modelClone = false);

	//デストラクタ
	virtual ~Model();

	//モデルの読み込み
	void Load();

	//モデルの解放
	void Release();

	//更新
	void Update();

	//描画
	void Draw(const Transform& transform);

	//アニメーションの登録
	void Register(const char* animeFileName);

	//アニメーションの切り替え
	void PlayAnime(int animeIndex);

	//モデルの識別番号を取得
	int GetModelHandle()
	{
		return m_modelHandle;
	}
};