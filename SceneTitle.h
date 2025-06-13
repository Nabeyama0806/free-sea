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
	std::vector<int> m_select;	//選択されているキャラクター

	Node* m_rootNode;
	Transform m_transform;
	Sprite* m_sprite;
	int m_padAmount;
	int m_bgm;

public:
	//コンストラクタ
	SceneTitle() :
		m_phase(Phase::Home),
		m_rootNode(nullptr),
		m_sprite(nullptr),
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