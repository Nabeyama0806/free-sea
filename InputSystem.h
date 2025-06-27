#pragma once
#include "Vector2.h"
#include "DxLib.h"

class InputSystem
{
public:
	static constexpr int MaxPadAmount = 4;				//パッドの最大数

	enum class ActionMap
	{
		Player1,	
		Player2,
		Player3,	
		Player4,
		All,		//共通の入力

		Length
	};

	//シングルトン
	static InputSystem* GetInstance()
	{
		static InputSystem instance;
		return &instance;
	}

public:
	//何かのキーが押された瞬間
	bool IsAnyKeyDown();

	//何かのキーが押されている
	bool IsAnyKeyPress();

	//接続されているパッドの数を取得
	int GetPadAmount() const
	{
		return GetJoypadNum();
	}

	//左スティックによる移動入力
	Vector2 MoveValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//右スティックによる回転入力
	Vector2 RotationValue(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//弾を撃つ
	bool BulletShot(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//決定
	bool IsDecision(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//決定を離す
	bool IsDecisionUp(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//左を選択
	bool SelectLeft(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);

	//右を選択
	bool SelectRight(InputSystem::ActionMap actionMap = InputSystem::ActionMap::All);
};