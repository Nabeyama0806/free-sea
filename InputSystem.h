#pragma once
#include "Vector2.h"
#include "DxLib.h"

class InputSystem
{
public:
	static constexpr int MaxPadAmount = 4;				//�p�b�h�̍ő吔

	enum class ActionMap
	{
		Player1,	
		Player2,
		Player3,	
		Player4,
		All,		//���ʂ̓���

		Length
	};

	//�V���O���g��
	static InputSystem* GetInstance()
	{
		static InputSystem instance;
		return &instance;
	}

public:
	//�����̃L�[�������ꂽ�u��
	bool IsAnyKeyDown();

	//�����̃L�[��������Ă���
	bool IsAnyKeyPress();

	//�ڑ�����Ă���p�b�h�̐����擾
	int GetPadAmount() const
	{
		return GetJoypadNum();
	}

	//���X�e�B�b�N�ɂ��ړ�����
	Vector2 MoveValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//�E�X�e�B�b�N�ɂ���]����
	Vector2 RotationValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//�e������
	bool BulletShot(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//����
	bool IsDecision(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//����𗣂�
	bool IsDecisionUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//����I��
	bool SelectLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//�E��I��
	bool SelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);
};