#pragma once
#include "SceneBase.h"

class Node;
class Character;

class SceneResult : public SceneBase
{
private:
	static constexpr float WaitTransitionTime = 1.5f;

	Node* m_rootNode;
	Character* m_character;

	float m_waitTransitionTime;

public:
	//コンストラクタ
	SceneResult(Character* character) :
		m_character(character),
		m_rootNode(nullptr),
		m_waitTransitionTime(WaitTransitionTime) 
	{
	}

	virtual void Preload() override {};
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};