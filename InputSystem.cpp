#include "InputSystem.h"
#include "Input.h"

//�p�b�h�̐����擾
int InputSystem::GetPadAmount() const
{
	return Input::GetInstance()->GetPadAmount();
}

//�����̃L�[�������ꂽ�u��
bool InputSystem::IsAnyKeyDown()
{
	return Input::GetInstance()->IsAnyKeyDown();
}

//�����̃L�[��������Ă���
bool InputSystem::IsAnyKeyPress()
{
	return Input::GetInstance()->IsAnyKeyPress();
}

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

//�e������
bool InputSystem::BulletShot(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadLeftTriggerPress(actionMap) || Input::GetInstance()->IsPadRightTriggerPress(actionMap);
}

// ����
bool InputSystem::IsDecision(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_1, actionMap);
}

//����𗣂�
bool InputSystem::IsDecisionUp(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadUp(PAD_INPUT_1, actionMap);
}

//����I��
bool InputSystem::SelectLeft(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_LEFT, actionMap); 
}

//�E��I��
bool InputSystem::SelectRight(InputSystem::ActionMap actionMap)
{
	return Input::GetInstance()->IsPadDown(PAD_INPUT_RIGHT, actionMap);
}
