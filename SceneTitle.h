#pragma once
#include "SceneBase.h"
#include "Transform.h"
#include "Node.h"
#include "InputSystem.h"
#include "ModelLoader.h"
#include "Sprite.h"
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
	const std::list<const char*> ModelPreload =
	{
		"Resource/Model/bullet_blue.mv1",
		"Resource/Model/bullet_green.mv1",
		"Resource/Model/bullet_red.mv1",
		"Resource/Model/bullet_pink.mv1",
	};

	//弾の種類
	/*const char* CharacterImage[static_cast<int>(Bullet::Type::Length)] =
	{
		"Resource/Texture/reflection.png",
		"Resource/Texture/straight.png",
		"Resource/Texture/diffusion.png",
		"Resource/Texture/laser.png",
	};*/


	const Vector2 DrawPosOffset[InputSystem::MaxPadAmount] =
	{
		Vector2(-430.0f, -110.0f),
		Vector2(630.0f, -110.0f),
		Vector2(-430.0f, 325.0f),
		Vector2(630.0f, 325.0f),
	};

	std::vector<int> m_select;	//選択されている弾

	Node* m_rootNode;
	Transform m_transform;
	Sprite* m_sprites[InputSystem::MaxPadAmount];
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
		//モデルのプリロード
		for (const char* modelPath : ModelPreload)
		{
			ModelLoader::GetInstance()->Load(modelPath);
		}
	}

	virtual void Initialize() override;				//初期化
	virtual void Finalize() override;				//終了
	virtual SceneBase* Update() override;			//更新
	virtual void Draw() override;					//描画
};