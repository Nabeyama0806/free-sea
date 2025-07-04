#pragma once
#include "ModelActor.h"

class Stage : public ModelActor
{
private:
	static constexpr int FrameIndex = -1;

	ModelActor* m_model;
	int m_modelHandle;

public:
	//コンストラクタ
	Stage() :
		ModelActor("StageMesh", "Resource/Model/ground_mesh.mv1"),
		m_model(nullptr),
		m_modelHandle(0)
	{
		//見た目のモデルを読み込む
		AddChild(new ModelActor("Stage", "Resource/Model/ground.mv1"));
	}

	int GetFrameIndex()
	{
		return FrameIndex;
	}
};