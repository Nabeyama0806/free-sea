#include "Button.h"
#include "Input.h"
#include "SoundManager.h"

// コンストラクタ
Button::Button(const Vector2& size, int mouseButton, std::function<void()> callbackFunction) :
	m_size(size),
	m_mouseButton(mouseButton),
	m_callbackFunction(callbackFunction),
	m_isClickDown(false)
{
}

//マウスカーソルがボタンの範囲内にあるかを判定
bool Button::IsMouseContain(const Vector2& position)
{
	// 矩形(ボタン)に点(マウス)が含まれているか
	Vector2 mousePoint = Input::GetInstance()->GetMousePoint();
	if (position.x - m_size.x / 2 <= mousePoint.x && mousePoint.x <= position.x + m_size.x / 2
		&& position.y - m_size.y / 2 <= mousePoint.y && mousePoint.y <= position.y + m_size.y / 2)
	{
		return true;
	}
	return false;
}

//更新
void Button::Update(const Vector2& position)
{
	// ボタン上で指定されたマウスボタンが押されたか
	if (Input::GetInstance()->IsDecision())
	{
		m_isClickDown = IsMouseContain(position);
	}

	// ボタン上で指定されたマウスボタンが離したか
	if (m_isClickDown && Input::GetInstance()->IsDecisionUp())
	{
		m_isClickDown = false;
		if (IsMouseContain(position))
		{
			// コールバック関数呼び出し
			m_callbackFunction();

			//効果音の再生
			SoundManager::Play("Resource/sound/se_start.mp3");
		}
	}
}

//描画
void Button::Draw(const Vector2& position)
{
	//ボタン上にマウスカーソルが無ければ何もしない
	if (!IsMouseContain(position)) return;

	//描画
	DrawBox(
		static_cast<int>(position.x - m_size.x / 2), static_cast<int>(position.y - m_size.y / 2),
		static_cast<int>(position.x + m_size.x / 2), static_cast<int>(position.y + m_size.y / 2),
		GetColor(255, 255, 0), 0);
}
