#pragma once
#include "Vector2.h"
#include "DxLib.h"

class InputSystem
{
public:
	enum class ActionMap
	{
		Player1,	
		Player2,
		Player3,	
		Player4,
		All,		//���ʂ̓���

		Length,
	};

	//�V���O���g��
	static InputSystem* GetInstance()
	{
		static InputSystem instance;
		return &instance;
	}

public:
	//���X�e�B�b�N�ɂ��ړ�����
	Vector2 MoveValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//�E�X�e�B�b�N�ɂ���]����
	Vector2 RotationValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ��ړ�	
	bool MoveUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ���ړ�
	bool MoveDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ���ړ�
	bool MoveLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �E�ړ�
	bool MoveRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �{�g���𓊂���
	bool BulletShot(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ����
	bool IsDecision(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ����𗣂�
	bool IsDecisionUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �J�����̎��_�ύX
	bool IsCameraChange(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �^�C�g���̑I��
	bool TitleSelectLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	bool TitleSelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// �^�C�g���̃X�e�[�W�I��
	bool StageSelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);
};