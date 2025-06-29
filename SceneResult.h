#pragma once
#include "SceneBase.h"
#include "Transform.h"
#include "InputSystem.h"

class Node;
class Sprite;

class SceneResult : public SceneBase
{
private:
	static constexpr float WaitTransitionTime = 1.5f;

	//画像のファイルパス
	const char* TextureFilePath[InputSystem::MaxPadAmount] =
	{
		"Resource/Texture/title_logo.png",
		"Resource/Texture/result_green.png",
		"Resource/Texture/result_red.png",
		"Resource/Texture/result_pink.png",
	};

	//画像の名前
	const char* TextureName[InputSystem::MaxPadAmount] =
	{
		"blue_bird",
		"green_bird",
		"red_bird",
		"pink_bird",
	};

	Node* m_rootNode;
	Sprite* m_sprite;
	Transform m_transform;

	int m_playerIndex;
	float m_waitTransitionTime;

public:
	//コンストラクタ
	SceneResult(int playerIndex) :
		m_playerIndex(playerIndex),
		m_rootNode(nullptr),
		m_sprite(nullptr),
		m_waitTransitionTime(WaitTransitionTime) 
	{
	}

	virtual void Preload() override {};
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};