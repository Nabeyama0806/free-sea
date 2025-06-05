#pragma once
#include "Vector2.h"
#include "DxLib.h"

class InputSystem
{
public:
	enum class ActionMap
	{
		All,		//���ʂ̓���
		Player1,	
		Player2,

		Length,
	};

	//�V���O���g��
	static InputSystem* GetInstance()
	{
		static InputSystem instance;
		return &instance;
	}

public:
	//�X�e�B�b�N�̓��͒l
	Vector2 MoveValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ��ړ�	
	bool MoveUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ���ړ�
	bool MoveDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ���ړ�
	bool MoveLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �E�ړ�
	bool MoveRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �{�g���𓊂���
	bool NewBottle(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ����
	bool IsDecision(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ����𗣂�
	bool IsDecisionUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	bool IsReLoadMap(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �J�����̎��_�ύX
	bool IsCameraChange(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �^�C�g���̑I��
	bool TitleSelectLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	bool TitleSelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �^�C�g���̃X�e�[�W�I��
	bool StageSelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);
};