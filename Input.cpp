#include "Input.h"
#include "InputSystem.h"
#include "DxLib.h"
#include <cstring>

//更新
void Input::Update()
{
	//キーボード

	//前フレームのキー入力状態を保存
	std::memcpy(m_keyStatePost, m_keyState, sizeof(char) * KeyStateNum);

	//現フレームのキー入力状態を取得
	GetHitKeyStateAll(m_keyState);

	//マウス

	//前フレームのマウスボタン入力状態を保存
	m_mouseButtonPost = m_mouseButton;

	//現在のマウスボタン入力状態を取得
	m_mouseButton = DxLib::GetMouseInput();

	//マウス位置を取得
	int mouseX = 0;
	int mouseY = 0;
	DxLib::GetMousePoint(&mouseX, &mouseY);
	m_mousePoint = Vector2(mouseX, mouseY);

	//マウスホイールを取得
	m_mouseWheel = DxLib::GetMouseWheelRotVol();

	// パッド
	for (int i = 0; i < static_cast<int>(InputSystem::ActionMap::Length); ++i)
	{
		//ボタン
		m_padButtonPost[i] = m_padButton[i];
		m_padButton[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);

		//スティック
		int x, y;
		GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1 + i);
		m_padLeftStick[i] = Vector2(x, y);
	}


	//// パッドのトリガーの状態を取得
	//XINPUT_STATE state;
	//GetJoypadXInputState(DX_INPUT_PAD1, &state);

	//// 右トリガー
	//m_padRightTriggerPost = m_padRightTrigger;
	//m_padRightTrigger = state.RightTrigger;

	//// 左トリガー
	//m_padLeftTriggerPost = m_padLeftTrigger;
	//m_padLeftTrigger = state.LeftTrigger;
}

//何かキーが押された瞬間
bool Input::IsAnyKeyDown()
{
	//マウス
	if (m_mouseButton && (m_mouseButton ^ m_mouseButtonPost))
	{
		return true;
	}

	//キーボード

	//配列の比較
	if (std::memcpy(m_keyStatePost, m_keyState, sizeof(char) * KeyStateNum) == 0)
	{
		return false;
	}

	// パッド
	for (int i = 0; i < static_cast<int>(InputSystem::ActionMap::Length); ++i)
	{
		if ((m_padButton[i] & ~m_padButtonPost[i]) != 0)
		{
			return true;
		}
	}

	if (m_padRightTrigger != 0 && m_padRightTriggerPost == 0 ||
		m_padLeftTrigger != 0 && m_padLeftTriggerPost == 0)
	{
		return true;
	}

	//配列から１を探し出す
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}

//何かキーが押されている
bool Input::IsAnyKeyPress()
{
	//マウス
	if (m_mouseButton)
	{
		return true;
	}

	// パッド
	for (int i = 0; i < static_cast<int>(InputSystem::ActionMap::Length); ++i)
	{
		if (m_padButton[i] != 0)
		{
			return true;
		}
	}

	if (m_padRightTrigger != 0 || m_padLeftTrigger != 0)
	{
		return true;
	}

	//キーボード

	//配列から１を探し出す
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}