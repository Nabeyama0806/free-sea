#include "InputSystem.h"
#include "Input.h"

//���X�e�B�b�N�ɂ��ړ�����
Vector2 InputSystem::MoveValue(InputSystem::ActionMap actionMap)
{
	Vector2 tmp = Input::GetInstance()->GetPadLeftStick(actionMap);
	if(tmp != Vector2()) tmp.Normalize();
	return tmp;
}

//�E�X�e�B�b�N�ɂ���]����
Vector2 InputSystem::RotationValue(InputSystem::ActionMap actionMap)
{
	Vector2 tmp = Input::GetInstance()->GetPadRightStick(actionMap);
	if (tmp != Vector2()) tmp.Normalize();
	return tmp;
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

//�ˌ�
bool InputSystem::BulletShot(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadLeftTriggerPress(actionMap) || Input::GetInstance()->IsPadRightTriggerPress(actionMap);
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

// �J�����̎��_�ύX
bool InputSystem::IsCameraChange(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_10, actionMap);
}

// �^�C�g���̑I��
bool InputSystem::SelectLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_LEFT, actionMap); 
}

bool InputSystem::SelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_RIGHT, actionMap);
}
