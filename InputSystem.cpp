#include "InputSystem.h"
#include "Input.h"

//�X�e�B�b�N�̓��͒l
Vector2 InputSystem::MoveValue(InputSystem::ActionMap actionMap)
{
	return (Input::GetInstance()->GetPadLeftStick(actionMap)).Normalize();
}

// ��ړ�	
bool InputSystem::MoveUp(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_UP, actionMap);
}

// ���ړ�
bool InputSystem::MoveDown(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_DOWN, actionMap);
}

// ���ړ�
bool InputSystem::MoveLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_LEFT, actionMap);
}

// �E�ړ�
bool InputSystem::MoveRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadPress(PAD_INPUT_RIGHT, actionMap);
}

// �{�g���𓊂���
bool InputSystem::NewBottle(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadRightTriggerDown(actionMap) || Input::GetInstance()->IsPadLeftTriggerDown(actionMap);
}

// ����
bool InputSystem::IsDecision(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_1, actionMap);
}

// ����𗣂�
bool InputSystem::IsDecisionUp(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadUp(PAD_INPUT_1, actionMap);
}

bool InputSystem::IsReLoadMap(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_7, actionMap);
}

// �J�����̎��_�ύX
bool InputSystem::IsCameraChange(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_10, actionMap);
}

// �^�C�g���̑I��
bool InputSystem::TitleSelectLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_LEFT, actionMap);
}

bool InputSystem::TitleSelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_RIGHT, actionMap);
}

// �^�C�g���̃X�e�[�W�I��
bool InputSystem::StageSelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_5, actionMap);
}