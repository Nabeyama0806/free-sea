#include "Input.h"
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

	//マウスの左ボタンが押されたら、Zキーが入力されたことにする
	if (m_mouseButton & MOUSE_INPUT_LEFT) m_keyState[KEY_INPUT_Z] = 1;

	// パッド
	m_padButtonPost = m_padButton;
	m_padButton = GetJoypadInputState(DX_INPUT_PAD1);

	// パッドのトリガーの状態を取得
	XINPUT_STATE state;
	GetJoypadXInputState(DX_INPUT_PAD1, &state);
	// 右トリガー
	m_padRightTriggerPost = m_padRightTrigger;
	m_padRightTrigger = state.RightTrigger;
	// 左トリガー
	m_padLeftTriggerPost = m_padLeftTrigger;
	m_padLeftTrigger = state.LeftTrigger;

#ifdef _DEBUG
	// パッドのShareボタンをESCキーにする
	if (IsPadDown(PAD_INPUT_7)) m_keyState[KEY_INPUT_ESCAPE] = 1;
#endif // DEBUG
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
	if ((m_padButton & ~m_padButtonPost) != 0)
	{
		return true;
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
	if (m_padButton != 0)
	{
		return true;
	}

	if (m_padRightTrigger != 0 || m_padLeftTrigger != 0)
	{
		return true;
	}

	//キーボード

	//配列から１を探し出す
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}