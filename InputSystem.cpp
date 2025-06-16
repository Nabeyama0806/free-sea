#include "InputSystem.h"
#include "Input.h"

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

// 上移動	
bool InputSystem::MoveUp(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_UP, actionMap);
}

// 下移動
bool InputSystem::MoveDown(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_DOWN, actionMap);
}

// 左移動
bool InputSystem::MoveLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_LEFT, actionMap);
}

// 右移動
bool InputSystem::MoveRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_RIGHT, actionMap);
}

//射撃
bool InputSystem::BulletShot(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadLeftTriggerPress(actionMap) || Input::GetInstance()->IsPadRightTriggerPress(actionMap);
}

// 決定
bool InputSystem::IsDecision(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_1, actionMap);
}

// 決定を離す
bool InputSystem::IsDecisionUp(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadUp(PAD_INPUT_1, actionMap);
}

// カメラの視点変更
bool InputSystem::IsCameraChange(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_10, actionMap);
}

// タイトルの選択
bool InputSystem::SelectLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_LEFT, actionMap); 
}

bool InputSystem::SelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_RIGHT, actionMap);
}
