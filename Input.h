#pragma once
#include "Vector2.h"
#include "DxLib.h"

#define KEY_INPUT_ENTER KEY_INPUT_RETURN

//入力クラス
class Input
{
private:
	//キーボード
	static constexpr int KeyStateNum = 256;	//キー入力状態の要素数
	static constexpr float PadStickSensitivity = 0.02f;	//スティックの感度
	static constexpr int PadTriggerSensitivity = 100;	//トリガーの感度(100/256)

	char m_keyState[KeyStateNum];		//現フレームのキー入力状態
	char m_keyStatePost[KeyStateNum];	//前フレームのキー入力状態

	//マウス
	Vector2 m_mousePoint;		//マウス位置
	int m_mouseWheel;			//マウスホイール
	int m_mouseButton;			//現フレームのマウスボタン入力状態
	int m_mouseButtonPost;		//前フレームのマウスボタン入力状態

	// パッド
	int m_padButton;
	int m_padButtonPost;

	int m_padRightTrigger;	// 右トリガーの状態
	int m_padRightTriggerPost;

	int m_padLeftTrigger;	// 左トリガーの状態
	int m_padLeftTriggerPost;

	//コンストラクタ
	Input() :
		m_keyState{ 0 },
		m_keyStatePost{ 0 },
		m_mouseWheel(0),
		m_mouseButton(0),
		m_mouseButtonPost(0),
		m_padButton(0),
		m_padButtonPost(0),
		m_padRightTrigger(0),
		m_padRightTriggerPost(0),
		m_padLeftTrigger(0),
		m_padLeftTriggerPost(0) {
	}	//配列の初期化は（）ではなく｛｝を使う

public:
	//シングルトン
	static Input* GetInstance()
	{
		static Input instance;
		return &instance;
	}

	//更新
	void Update();

	//キーが押された瞬間
	bool IsKeyDown(int key)
	{
		return !m_keyStatePost[key] && m_keyState[key];
	}

	//キーが押されている
	bool IsKeyPress(int key)
	{
		return m_keyState[key];
	}

	//キーが離された瞬間
	bool IsKeyUp(int key)
	{
		return m_keyStatePost[key] && !m_keyState[key];
	}

	//何かのキーが押された瞬間
	bool IsAnyKeyDown();

	//何かのキーが押されている
	bool IsAnyKeyPress();

	//マウス位置を取得
	Vector2 GetMousePoint()
	{
		return	m_mousePoint;
	}

	// マウス位置を設定
	void SetMousePoint(int posX, int posY)
	{
		DxLib::SetMousePoint(posX, posY);
		m_mousePoint = Vector2(posX, posY);
	}

	// マウスカーソルの表示
	void SetMouseDispFlag(bool isDisp)
	{
		DxLib::SetMouseDispFlag(isDisp);
	}

	//マウスホイールを取得
	int GetMouseHweelRot()
	{
		return m_mouseWheel;
	}

	//マウスボタンが押された瞬間
	bool IsMouseDown(int button)
	{
		return (m_mouseButton & button) && !(m_mouseButtonPost & button);
	}

	//マウスボタンが押されている時
	bool IsMousePress(int button)
	{
		return (m_mouseButton & button);
	}

	//マウスボタンが離された瞬間
	bool IsMouseUp(int button)
	{
		return !(m_mouseButton & button) && (m_mouseButtonPost & button);
	}

	// パッドボタンが押された瞬間
	bool IsPadDown(int button)
	{
		return (m_padButton & button) && !(m_padButtonPost & button);
	}

	// パッドボタンが押されている
	bool IsPadPress(int button)
	{
		return (m_padButton & button);
	}

	// パッドボタンが離された瞬間
	bool IsPadUp(int button)
	{
		return !(m_padButton & button) && (m_padButtonPost & button);
	}

	bool IsPadRightTriggerDown()
	{
		// トリガーの状態が100以上で、前フレームのトリガーの状態が100未満
		return m_padRightTrigger >= PadTriggerSensitivity && m_padRightTriggerPost < PadTriggerSensitivity;
	}

	bool IsPadRightTriggerUp()
	{
		// トリガーの状態が100未満で、前フレームのトリガーの状態が100以上
		return m_padRightTrigger < PadTriggerSensitivity && m_padRightTriggerPost >= PadTriggerSensitivity;
	}

	bool IsPadRightTriggerPress()
	{
		// トリガーの状態が100以上
		return m_padRightTrigger >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerDown()
	{
		// トリガーの状態が100以上で、前フレームのトリガーの状態が100未満
		return m_padLeftTrigger >= PadTriggerSensitivity && m_padLeftTriggerPost < PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerUp()
	{
		// トリガーの状態が100未満で、前フレームのトリガーの状態が100以上
		return m_padLeftTrigger < PadTriggerSensitivity && m_padLeftTriggerPost >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerPress()
	{
		// トリガーの状態が100以上
		return m_padLeftTrigger >= PadTriggerSensitivity;
	}

	void SetPadStick(Vector2 movePadPoint)
	{
		m_mousePoint += movePadPoint * PadStickSensitivity;
		// マウスカーソルの位置を設定
		SetMousePoint(static_cast<int>(m_mousePoint.x), static_cast<int>(m_mousePoint.y));
	}

	// インプットシステム
	// 上移動	
	bool MoveUp()
	{
		return IsKeyPress(KEY_INPUT_W) || IsPadPress(PAD_INPUT_UP);
	}

	// 下移動
	bool MoveDown()
	{
		return IsKeyPress(KEY_INPUT_S) || IsPadPress(PAD_INPUT_DOWN);
	}

	// 左移動
	bool MoveLeft()
	{
		return IsKeyPress(KEY_INPUT_A) || IsPadPress(PAD_INPUT_LEFT);
	}

	// 右移動
	bool MoveRight()
	{
		return IsKeyPress(KEY_INPUT_D) || IsPadPress(PAD_INPUT_RIGHT);
	}

	// ボトルを投げる
	bool NewBottle()
	{
		return IsMouseDown(MOUSE_INPUT_LEFT) || IsPadRightTriggerDown() || IsPadLeftTriggerDown();
	}

	// 決定
	bool IsDecision()
	{
		return IsPadDown(PAD_INPUT_1) || IsMouseDown(MOUSE_INPUT_LEFT);
	}

	// 決定を離す
	bool IsDecisionUp()
	{
		return IsPadUp(PAD_INPUT_1) || IsMouseUp(MOUSE_INPUT_LEFT);
	}

	bool IsReLoadMap()
	{
		return IsKeyDown(KEY_INPUT_R) || IsPadDown(PAD_INPUT_7);
	}

	// カメラの視点変更
	bool IsCameraChange()
	{
		return IsKeyDown(KEY_INPUT_SPACE) || IsPadDown(PAD_INPUT_10);
	}

	// タイトルの選択
	bool TitleSelectLeft()
	{
		return IsPadDown(PAD_INPUT_LEFT);
	}

	bool TitleSelectRight()
	{
		return IsPadDown(PAD_INPUT_RIGHT);
	}

	// タイトルのステージ選択
	bool StageSelectRight()
	{
		return IsPadDown(PAD_INPUT_5);
	}

	bool StageSelectLeft()
	{
		return IsPadDown(PAD_INPUT_6);
	}
};