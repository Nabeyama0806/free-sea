#include "InputSystem.h"
#include "Input.h"

//スティックの入力値
Vector2 InputSystem::MoveValue(InputSystem::ActionMap actionMap)
{
	return (Input::GetInstance()->GetPadLeftStick(actionMap)).Normalize();
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

// ボトルを投げる
bool InputSystem::NewBottle(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadRightTriggerDown(actionMap) || Input::GetInstance()->IsPadLeftTriggerDown(actionMap);
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

bool InputSystem::IsReLoadMap(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_7, actionMap);
}

// カメラの視点変更
bool InputSystem::IsCameraChange(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_10, actionMap);
}

// タイトルの選択
bool InputSystem::TitleSelectLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_LEFT, actionMap);
}

bool InputSystem::TitleSelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_RIGHT, actionMap);
}

// タイトルのステージ選択
bool InputSystem::StageSelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_5, actionMap);
}