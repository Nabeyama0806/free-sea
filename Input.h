#pragma once
#include "Vector2.h"
#include "InputSystem.h"
#include "DxLib.h"

#define KEY_INPUT_ENTER KEY_INPUT_RETURN

//���̓N���X
class Input
{
private:
	//�L�[�{�[�h
	static constexpr int KeyStateNum = 256;	//�L�[���͏�Ԃ̗v�f��
	static constexpr float PadStickSensitivity = 0.02f;	//�X�e�B�b�N�̊��x
	static constexpr int PadTriggerSensitivity = 100;	//�g���K�[�̊��x(100/256)

	char m_keyState[KeyStateNum];		//���t���[���̃L�[���͏��
	char m_keyStatePost[KeyStateNum];	//�O�t���[���̃L�[���͏��

	//�}�E�X
	Vector2 m_mousePoint;		//�}�E�X�ʒu
	int m_mouseWheel;			//�}�E�X�z�C�[��
	int m_mouseButton;			//���t���[���̃}�E�X�{�^�����͏��
	int m_mouseButtonPost;		//�O�t���[���̃}�E�X�{�^�����͏��

	// �p�b�h
	static constexpr float PadStickDeadZone = 32767 * 0.2f;	// �X�e�B�b�N�̃f�b�h�]�[��

	int m_padButton[static_cast<int>(InputSystem::ActionMap::Length)];
	int m_padButtonPost[static_cast<int>(InputSystem::ActionMap::Length)];

	Vector2 m_padLeftStick[static_cast<int>(InputSystem::ActionMap::Length)];
	Vector2 m_padRightStick[static_cast<int>(InputSystem::ActionMap::Length)];

	int m_padRightTrigger[static_cast<int>(InputSystem::ActionMap::Length)];	// �E�g���K�[�̏��
	int m_padRightTriggerPost[static_cast<int>(InputSystem::ActionMap::Length)];

	int m_padLeftTrigger[static_cast<int>(InputSystem::ActionMap::Length)];	// ���g���K�[�̏��
	int m_padLeftTriggerPost[static_cast<int>(InputSystem::ActionMap::Length)];

	//�R���X�g���N�^
	Input() :
		m_keyState{ 0 },
		m_keyStatePost{ 0 },
		m_mouseWheel{ 0 },
		m_mouseButton{ 0 },
		m_mouseButtonPost(0),
		m_padButton{ 0 },
		m_padButtonPost{ 0 },
		m_padRightTrigger{ 0 },
		m_padRightTriggerPost{ 0 },
		m_padLeftTrigger{ 0 },
		m_padLeftTriggerPost{ 0 }
	{
	}	

public:
	//�V���O���g��
	static Input* GetInstance()
	{
		static Input instance;
		return &instance;
	}

	//�X�V
	void Update();

	//�L�[�������ꂽ�u��
	bool IsKeyDown(int key)
	{
		return !m_keyStatePost[key] && m_keyState[key];
	}

	//�L�[��������Ă���
	bool IsKeyPress(int key)
	{
		return m_keyState[key];
	}

	//�L�[�������ꂽ�u��
	bool IsKeyUp(int key)
	{
		return m_keyStatePost[key] && !m_keyState[key];
	}

	//�����̃L�[�������ꂽ�u��
	bool IsAnyKeyDown();

	//�����̃L�[��������Ă���
	bool IsAnyKeyPress();

	//�}�E�X�ʒu���擾
	Vector2 GetMousePoint()
	{
		return	m_mousePoint;
	}

	// �}�E�X�ʒu��ݒ�
	void SetMousePoint(int posX, int posY)
	{
		DxLib::SetMousePoint(posX, posY);
		m_mousePoint = Vector2(posX, posY);
	}

	// �}�E�X�J�[�\���̕\��
	void SetMouseDispFlag(bool isDisp)
	{
		DxLib::SetMouseDispFlag(isDisp);
	}

	//�}�E�X�z�C�[�����擾
	int GetMouseHweelRot()
	{
		return m_mouseWheel;
	}

	//�}�E�X�{�^���������ꂽ�u��
	bool IsMouseDown(int button)
	{
		return (m_mouseButton & button) && !(m_mouseButtonPost & button);
	}

	//�}�E�X�{�^����������Ă��鎞
	bool IsMousePress(int button)
	{
		return (m_mouseButton & button);
	}

	//�}�E�X�{�^���������ꂽ�u��
	bool IsMouseUp(int button)
	{
		return !(m_mouseButton & button) && (m_mouseButtonPost & button);
	}

	// �p�b�h�{�^���������ꂽ�u��
	bool IsPadDown(int button, InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		return (m_padButton[static_cast<int>(actionMap)] & button) && !(m_padButtonPost[static_cast<int>(actionMap)] & button);
	}

	// �p�b�h�{�^����������Ă���
	bool IsPadPress(int button, InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		return (m_padButton[static_cast<int>(actionMap)] & button);
	}

	// �p�b�h�{�^���������ꂽ�u��
	bool IsPadUp(int button, InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		return !(m_padButton[static_cast<int>(actionMap)] & button) && (m_padButtonPost[static_cast<int>(actionMap)] & button);
	}

	//�X�e�B�b�N�̓��͒l
	Vector2 GetPadLeftStick(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		Vector2 input = m_padLeftStick[static_cast<int>(actionMap)];

		// �f�b�h�]�[����K�p
		if (input.SqrMagnitude() < PadStickDeadZone * PadStickDeadZone)
		{
			m_padLeftStick[static_cast<int>(actionMap)] = Vector2(0, 0);
		}

		return m_padLeftStick[static_cast<int>(actionMap)];
	}
	Vector2 GetPadRightStick(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		Vector2 input = m_padRightStick[static_cast<int>(actionMap)];

		// �f�b�h�]�[����K�p
		if (input.SqrMagnitude() < PadStickDeadZone * PadStickDeadZone)
		{
			m_padRightStick[static_cast<int>(actionMap)] = Vector2(0, 0);
		}

		return m_padRightStick[static_cast<int>(actionMap)];
	}

	bool IsPadRightTriggerDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// �g���K�[�̏�Ԃ�100�ȏ�ŁA�O�t���[���̃g���K�[�̏�Ԃ�100����
		return m_padRightTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity && m_padRightTriggerPost[static_cast<int>(actionMap)] < PadTriggerSensitivity;
	}

	bool IsPadRightTriggerUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// �g���K�[�̏�Ԃ�100�����ŁA�O�t���[���̃g���K�[�̏�Ԃ�100�ȏ�
		return m_padRightTrigger[static_cast<int>(actionMap)] < PadTriggerSensitivity && m_padRightTriggerPost[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	bool IsPadRightTriggerPress(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// �g���K�[�̏�Ԃ�100�ȏ�
		return m_padRightTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// �g���K�[�̏�Ԃ�100�ȏ�ŁA�O�t���[���̃g���K�[�̏�Ԃ�100����
		return m_padLeftTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity && m_padLeftTriggerPost[static_cast<int>(actionMap)] < PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// �g���K�[�̏�Ԃ�100�����ŁA�O�t���[���̃g���K�[�̏�Ԃ�100�ȏ�
		return m_padLeftTrigger[static_cast<int>(actionMap)] < PadTriggerSensitivity && m_padLeftTriggerPost[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerPress(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All)
	{
		// �g���K�[�̏�Ԃ�100�ȏ�
		return m_padLeftTrigger[static_cast<int>(actionMap)] >= PadTriggerSensitivity;
	}

	void SetPadStick(Vector2 movePadPoint)
	{
		m_mousePoint += movePadPoint * PadStickSensitivity;
		// �}�E�X�J�[�\���̈ʒu��ݒ�
		SetMousePoint(static_cast<int>(m_mousePoint.x), static_cast<int>(m_mousePoint.y));
	}
};