#include "Input.h"
#include "InputSystem.h"
#include "DxLib.h"
#include <cstring>

//�X�V
void Input::Update()
{
	//�L�[�{�[�h

	//�O�t���[���̃L�[���͏�Ԃ�ۑ�
	std::memcpy(m_keyStatePost, m_keyState, sizeof(char) * KeyStateNum);

	//���t���[���̃L�[���͏�Ԃ��擾
	GetHitKeyStateAll(m_keyState);

	//�}�E�X

	//�O�t���[���̃}�E�X�{�^�����͏�Ԃ�ۑ�
	m_mouseButtonPost = m_mouseButton;

	//���݂̃}�E�X�{�^�����͏�Ԃ��擾
	m_mouseButton = DxLib::GetMouseInput();

	//�}�E�X�ʒu���擾
	int mouseX = 0;
	int mouseY = 0;
	DxLib::GetMousePoint(&mouseX, &mouseY);
	m_mousePoint = Vector2(mouseX, mouseY);

	//�}�E�X�z�C�[�����擾
	m_mouseWheel = DxLib::GetMouseWheelRotVol();

	// �p�b�h
	int padAmount = GetJoypadNum();
	for (int i = 0; i < padAmount; ++i)
	{
		//�{�^��
		m_padButtonPost[i] = m_padButton[i];
		m_padButton[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
	}

	// �p�b�h�̃g���K�[�̏�Ԃ��擾
	for (int i = 0; i < padAmount; ++i)
	{
		XINPUT_STATE state;
		GetJoypadXInputState(DX_INPUT_PAD1 + i, &state);

		// �E�g���K�[
		m_padRightTriggerPost[i] = m_padRightTrigger[i];
		m_padRightTrigger[i] = state.RightTrigger;

		// ���g���K�[
		m_padLeftTriggerPost[i] = m_padLeftTrigger[i];
		m_padLeftTrigger[i] = state.LeftTrigger;

		//�E�X�e�B�b�N
		int rx, ry;
		rx = state.ThumbRX;
		ry = state.ThumbRY;
		m_padRightStick[i] = Vector2(rx, ry);

		//���X�e�B�b�N
		int lx, ly;
		lx = state.ThumbLX;
		ly = state.ThumbLY;
		m_padLeftStick[i] = Vector2(lx, ly);
	}
}

//�����L�[�������ꂽ�u��
bool Input::IsAnyKeyDown()
{
	//�}�E�X
	if (m_mouseButton && (m_mouseButton ^ m_mouseButtonPost))
	{
		return true;
	}

	//�L�[�{�[�h

	//�z��̔�r
	if (std::memcpy(m_keyStatePost, m_keyState, sizeof(char) * KeyStateNum) == 0)
	{
		return false;
	}

	// �p�b�h
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

	//�z�񂩂�P��T���o��
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}

//�����L�[��������Ă���
bool Input::IsAnyKeyPress()
{
	//�}�E�X
	if (m_mouseButton)
	{
		return true;
	}

	// �p�b�h
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

	//�L�[�{�[�h

	//�z�񂩂�P��T���o��
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}