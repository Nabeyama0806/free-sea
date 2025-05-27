#pragma once
#include "Vector2.h"
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
	int m_padButton;
	int m_padButtonPost;

	int m_padRightTrigger;	// �E�g���K�[�̏��
	int m_padRightTriggerPost;

	int m_padLeftTrigger;	// ���g���K�[�̏��
	int m_padLeftTriggerPost;

	//�R���X�g���N�^
	Input() :
		m_keyState{ 0 },
		m_keyStatePost{ 0 },
		m_mouseWheel(0),
		m_mouseButton(0),
		m_mouseButtonPost(0),
		m_padButton(0),
		m_padButtonPost(0),
		m_padRightTrigger(0),
		m_padRightTriggerPost(0),
		m_padLeftTrigger(0),
		m_padLeftTriggerPost(0) {
	}	//�z��̏������́i�j�ł͂Ȃ��o�p���g��

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
	bool IsPadDown(int button)
	{
		return (m_padButton & button) && !(m_padButtonPost & button);
	}

	// �p�b�h�{�^����������Ă���
	bool IsPadPress(int button)
	{
		return (m_padButton & button);
	}

	// �p�b�h�{�^���������ꂽ�u��
	bool IsPadUp(int button)
	{
		return !(m_padButton & button) && (m_padButtonPost & button);
	}

	bool IsPadRightTriggerDown()
	{
		// �g���K�[�̏�Ԃ�100�ȏ�ŁA�O�t���[���̃g���K�[�̏�Ԃ�100����
		return m_padRightTrigger >= PadTriggerSensitivity && m_padRightTriggerPost < PadTriggerSensitivity;
	}

	bool IsPadRightTriggerUp()
	{
		// �g���K�[�̏�Ԃ�100�����ŁA�O�t���[���̃g���K�[�̏�Ԃ�100�ȏ�
		return m_padRightTrigger < PadTriggerSensitivity && m_padRightTriggerPost >= PadTriggerSensitivity;
	}

	bool IsPadRightTriggerPress()
	{
		// �g���K�[�̏�Ԃ�100�ȏ�
		return m_padRightTrigger >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerDown()
	{
		// �g���K�[�̏�Ԃ�100�ȏ�ŁA�O�t���[���̃g���K�[�̏�Ԃ�100����
		return m_padLeftTrigger >= PadTriggerSensitivity && m_padLeftTriggerPost < PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerUp()
	{
		// �g���K�[�̏�Ԃ�100�����ŁA�O�t���[���̃g���K�[�̏�Ԃ�100�ȏ�
		return m_padLeftTrigger < PadTriggerSensitivity && m_padLeftTriggerPost >= PadTriggerSensitivity;
	}

	bool IsPadLeftTriggerPress()
	{
		// �g���K�[�̏�Ԃ�100�ȏ�
		return m_padLeftTrigger >= PadTriggerSensitivity;
	}

	void SetPadStick(Vector2 movePadPoint)
	{
		m_mousePoint += movePadPoint * PadStickSensitivity;
		// �}�E�X�J�[�\���̈ʒu��ݒ�
		SetMousePoint(static_cast<int>(m_mousePoint.x), static_cast<int>(m_mousePoint.y));
	}

	// �C���v�b�g�V�X�e��
	// ��ړ�	
	bool MoveUp()
	{
		return IsKeyPress(KEY_INPUT_W) || IsPadPress(PAD_INPUT_UP);
	}

	// ���ړ�
	bool MoveDown()
	{
		return IsKeyPress(KEY_INPUT_S) || IsPadPress(PAD_INPUT_DOWN);
	}

	// ���ړ�
	bool MoveLeft()
	{
		return IsKeyPress(KEY_INPUT_A) || IsPadPress(PAD_INPUT_LEFT);
	}

	// �E�ړ�
	bool MoveRight()
	{
		return IsKeyPress(KEY_INPUT_D) || IsPadPress(PAD_INPUT_RIGHT);
	}

	// �{�g���𓊂���
	bool NewBottle()
	{
		return IsMouseDown(MOUSE_INPUT_LEFT) || IsPadRightTriggerDown() || IsPadLeftTriggerDown();
	}

	// ����
	bool IsDecision()
	{
		return IsPadDown(PAD_INPUT_1) || IsMouseDown(MOUSE_INPUT_LEFT);
	}

	// ����𗣂�
	bool IsDecisionUp()
	{
		return IsPadUp(PAD_INPUT_1) || IsMouseUp(MOUSE_INPUT_LEFT);
	}

	bool IsReLoadMap()
	{
		return IsKeyDown(KEY_INPUT_R) || IsPadDown(PAD_INPUT_7);
	}

	// �J�����̎��_�ύX
	bool IsCameraChange()
	{
		return IsKeyDown(KEY_INPUT_SPACE) || IsPadDown(PAD_INPUT_10);
	}

	// �^�C�g���̑I��
	bool TitleSelectLeft()
	{
		return IsPadDown(PAD_INPUT_LEFT);
	}

	bool TitleSelectRight()
	{
		return IsPadDown(PAD_INPUT_RIGHT);
	}

	// �^�C�g���̃X�e�[�W�I��
	bool StageSelectRight()
	{
		return IsPadDown(PAD_INPUT_5);
	}

	bool StageSelectLeft()
	{
		return IsPadDown(PAD_INPUT_6);
	}
};