#pragma once
#include "SceneBase.h"
#include "CharacterBase.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Node.h"
#include "Transform.h"
#include <vector>

class Node;

//タイトルシーン
class SceneTitle : public SceneBase
{
private:
	enum class Phase
	{
		Home,		//始まり
		Select,		//キャラ選択
		GameStart,	//ゲーム開始

		Length
	};
	Phase m_phase;

private:
	const char* CharacterImage[static_cast<int>(CharacterBase::Type::Length)] =
	{
		"Resource/Texture/bird_blue.png",
		"Resource/Texture/bird_green.png",
		"Resource/Texture/bird_red.png",
		"Resource/Texture/bird_pink.png",
	};

	const char* TextureName[static_cast<int>(CharacterBase::Type::Length)] =
	{
		"BlurBird",
		"GreenBird",
		"RedBird",
		"PinkBird",
	};

	const Vector2 DrawPosOffset[static_cast<int>(CharacterBase::Type::Length)] =
	{
		Vector2(-300.0f, -50.0f),
		Vector2(300.0f, -50.0f),
		Vector2(-300.0f, 180.0f),
	};

	std::vector<int> m_select;	//選択されているキャラクター

	Node* m_rootNode;
	Transform m_transform;
	Sprite* m_sprites[static_cast<int>(CharacterBase::Type::Length)];
	int m_padAmount;
	int m_bgm;

public:
	//コンストラクタ
	SceneTitle() :
		m_phase(Phase::Home),
		m_rootNode(nullptr),
		m_sprites{nullptr},
		m_select(0) ,
		m_padAmount(0),
		m_bgm(0)
	{
	}

	virtual void Initialize() override;				//初期化
	virtual void Finalize() override;				//終了
	virtual SceneBase* Update() override;			//更新
	virtual void Draw() override;					//描画
};