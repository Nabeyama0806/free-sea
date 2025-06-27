#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Transform.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Bullet.h"
#include "ModelLoader.h"
#include <vector>

class Node;
class SpriteActor;

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
	static constexpr int MaxPadAmount = 4;	//パッドの数

	const std::list<const char*> ModelPreload =
	{
		"Resource/Model/bullet_blue.mv1",
		"Resource/Model/bullet_green.mv1",
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_pink.mv1",
	};

	const char* CharacterImage[static_cast<int>(Bullet::Type::Length)] =
	{
		"Resource/Texture/reflection.png",
		"Resource/Texture/straight.png",
		"Resource/Texture/diffusion.png",
		"Resource/Texture/laser.png",
	};

	const char* TextureName[static_cast<int>(Bullet::Type::Length)] =
	{
		"BlurBird",
		"GreenBird",
		"RedBird",
		"PinkBird",
	};

	const Vector2 DrawPosOffset[static_cast<int>(Bullet::Type::Length)] =
	{
		Vector2(-430.0f, -110.0f),
		Vector2(630.0f, -110.0f),
		Vector2(-430.0f, 325.0f),
		Vector2(630.0f, 325.0f),
	};

	std::vector<int> m_select;	//選択されている弾

	Node* m_rootNode;
	Transform m_transform;
	Sprite* m_sprites[static_cast<int>(Bullet::Type::Length)];
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

	virtual void Preload() override;				//プリロード
	virtual void Initialize() override;				//初期化
	virtual void Finalize() override;				//終了
	virtual SceneBase* Update() override;			//更新
	virtual void Draw() override;					//描画
};