#include "Input.h"
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

	//�}�E�X�̍��{�^���������ꂽ��AZ�L�[�����͂��ꂽ���Ƃɂ���
	if (m_mouseButton & MOUSE_INPUT_LEFT) m_keyState[KEY_INPUT_Z] = 1;

	// �p�b�h
	m_padButtonPost = m_padButton;
	m_padButton = GetJoypadInputState(DX_INPUT_PAD1);

	// �p�b�h�̃g���K�[�̏�Ԃ��擾
	XINPUT_STATE state;
	GetJoypadXInputState(DX_INPUT_PAD1, &state);
	// �E�g���K�[
	m_padRightTriggerPost = m_padRightTrigger;
	m_padRightTrigger = state.RightTrigger;
	// ���g���K�[
	m_padLeftTriggerPost = m_padLeftTrigger;
	m_padLeftTrigger = state.LeftTrigger;

#ifdef _DEBUG
	// �p�b�h��Share�{�^����ESC�L�[�ɂ���
	if (IsPadDown(PAD_INPUT_7)) m_keyState[KEY_INPUT_ESCAPE] = 1;
#endif // DEBUG
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
	if ((m_padButton & ~m_padButtonPost) != 0)
	{
		return true;
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
	if (m_padButton != 0)
	{
		return true;
	}

	if (m_padRightTrigger != 0 || m_padLeftTrigger != 0)
	{
		return true;
	}

	//�L�[�{�[�h

	//�z�񂩂�P��T���o��
	return std::memchr(m_keyState, 1, sizeof(char) * KeyStateNum) != nullptr;
}