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
		All,		//共通の入力

		Length,
	};

	//シングルトン
	static InputSystem* GetInstance()
	{
		static InputSystem instance;
		return &instance;
	}

public:
	//左スティックによる移動入力
	Vector2 MoveValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//右スティックによる回転入力
	Vector2 RotationValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// 上移動	
	bool MoveUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// 下移動
	bool MoveDown(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// 左移動
	bool MoveLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// 右移動
	bool MoveRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// ボトルを投げる
	bool BulletShot(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// 決定
	bool IsDecision(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// 決定を離す
	bool IsDecisionUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// カメラの視点変更
	bool IsCameraChange(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// タイトルの選択
	bool TitleSelectLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	bool TitleSelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	// タイトルのステージ選択
	bool StageSelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);
};