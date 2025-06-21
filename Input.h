#pragma once
#include "Vector2.h"
#include "InputSystem.h"
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
	static constexpr float PadStickDeadZone = 32767 * 0.2f;	// スティックのデッドゾーン

	int m_padButton[static_cast<int>(InputSystem::ActionMap::Length)];
	int m_padButtonPost[static_cast<int>(InputSystem::ActionMap::Length)];

	Vector2 m_padLeftStick[static_cast<int>(InputSystem::ActionMap::Length)];
	Vector2 m_padRightStick[static_cast<int>(InputSystem::ActionMap::Length)];

	int m_padRightTrigger[static_cast<int>(InputSystem::ActionMap::Length)];	// 右トリガーの状態
	int m_padRightTriggerPost[static_cast<int>(InputSystem::ActionMap::Length)];

	int m_padLeftTrigger[static_cast<int>(InputSystem::ActionMap::Length)];	// 左トリガーの状態
	int m_padLeftTriggerPost[static_cast<int>(InputSystem::ActionMap::Length)];

	//コンストラクタ
	Input() :
		m_keyState{ 0 },
		m_keyStatePost{ 0 },
		m_mouseWheel{ 0 },
		m_mouseButton{ 0 },
		m_mouseButtonPost(0),
		m_padButton{ 0 },
		m_padButtonPost{ 0 },
		m_padRightTrigger{ 0 },
		m_padRightTriggerPost{ 0 },
		m_padLeftTrigger{ 0 },
		m_padLeftTriggerPost{ 0 }
	{
	}	

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
	bool IsPadDown(int button, InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		return (m_padButton[static_cast<int>(actionMap)] & button) && !(m_padButtonPost[static_cast<int>(actionMap)] & button);
	}

	// パッドボタンが押されている
	bool IsPadPress(int button, InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		return (m_padButton[static_cast<int>(actionMap)] & button);
	}

	// パッドボタンが離された瞬間
	bool IsPadUp(int button, InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		return !(m_padButton[static_cast<int>(actionMap)] & button) && (m_padButtonPost[static_cast<int>(actionMap)] & button);
	}

	//スティックの入力値
	Vector2 GetPadLeftStick(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		Vector2 input = m_padLeftStick[static_cast<int>(actionMap)];

		// デッドゾーンを適用
		if (input.SqrMagnitude() < PadStickDeadZone * PadStickDeadZone)
		{
			m_padLeftStick[static_cast<int>(actionMap)] = Vector2(0, 0);
		}

		return m_padLeftStick[static_cast<int>(actionMap)];
	}
	Vector2 GetPadRightStick(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		Vector2 input = m_padRightStick[static_cast<int>(actionMap)];

		// デッドゾーンを適用
		if (input.SqrMagnitude() < PadStickDeadZone * PadStickDeadZone)
		{
			m_padRightStick[static_cast<int>(actionMap)] = Vector2(0, 0);
		}

		return m_padRightStick[static_cast<int>(actionMap)];
	}

	bool IsPadRightTriggerDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// トリガーの状態が100以上で、前フレームのトリガーの状態が100未満
		return m_padRightTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity && m_padRightTriggerPost[static_cast<int>(actionMap)] < PadTriggerSensitivity;
	}

	bool IsPadRightTriggerUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// トリガーの状態が100未満で、前フレームのトリガーの状態が100以上
		return m_padRightTrigger[static_cast<int>(actionMap)] < PadTriggerSensitivity && m_padRightTriggerPost[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	bool IsPadRightTriggerPress(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// トリガーの状態が100以上
		return m_padRightTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// トリガーの状態が100以上で、前フレームのトリガーの状態が100未満
		return m_padLeftTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity && m_padLeftTriggerPost[static_cast<int>(actionMap)] < PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// トリガーの状態が100未満で、前フレームのトリガーの状態が100以上
		return m_padLeftTrigger[static_cast<int>(actionMap)] < PadTriggerSensitivity && m_padLeftTriggerPost[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerPress(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// トリガーの状態が100以上
		return m_padLeftTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	void SetPadStick(Vector2 movePadPoint)
	{
		m_mousePoint += movePadPoint * PadStickSensitivity;
		// マウスカーソルの位置を設定
		SetMousePoint(static_cast<int>(m_mousePoint.x), static_cast<int>(m_mousePoint.y));
	}
};