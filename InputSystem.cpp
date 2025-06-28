#include "InputSystem.h"
#include "Input.h"

//パッドの数を取得
int InputSystem::GetPadAmount() const
{
	return Input::GetInstance()->GetPadAmount();
}

//何かのキーが押された瞬間
bool InputSystem::IsAnyKeyDown()
{
	return Input::GetInstance()->IsAnyKeyDown();
}

//何かのキーが押されている
bool InputSystem::IsAnyKeyPress()
{
	return Input::GetInstance()->IsAnyKeyPress();
}

//左スティックによる移動入力
Vector2 InputSystem::MoveValue(InputSystem::ActionMap actionMap)
{
	Vector2 tmp = Input::GetInstance()->GetPadLeftStick(actionMap);
	if(tmp != Vector2()) tmp.Normalize();
	return tmp;
}

//右スティックによる回転入力
Vector2 InputSystem::RotationValue(InputSystem::ActionMap actionMap)
{
	Vector2 tmp = Input::GetInstance()->GetPadRightStick(actionMap);
	if (tmp != Vector2()) tmp.Normalize();
	return tmp;
}

//弾を撃つ
bool InputSystem::BulletShot(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadLeftTriggerPress(actionMap) || Input::GetInstance()->IsPadRightTriggerPress(actionMap);
}

// 決定
bool InputSystem::IsDecision(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_1, actionMap);
}

//決定を離す
bool InputSystem::IsDecisionUp(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadUp(PAD_INPUT_1, actionMap);
}

//左を選択
bool InputSystem::SelectLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_LEFT, actionMap); 
}

//右を選択
bool InputSystem::SelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_RIGHT, actionMap);
}
