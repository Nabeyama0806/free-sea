#pragma once

//ゲームメインループクラス
class GameMain
{
private:
	int m_screen;	//自作スクリーン

public:
	//コンストラクタ(実行時に自動的に呼び出される関数)
	GameMain() :
		m_screen(0)
	{
	}

	//デストラクタ
	virtual ~GameMain();

	//メインループ実行
	void Run();
};