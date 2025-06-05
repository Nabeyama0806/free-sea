#pragma once
#include "ModelActor.h"

class Stage : public ModelActor
{
private:
	static constexpr int FrameIndex = -1;

	ModelActor* m_mesh;
	int m_modelHandle;

public:
	//コンストラクタ
	Stage() :
		ModelActor("StageMesh", "Environment/Ground_Mesh.mv1"),
		m_modelHandle(0)
	{
		m_mesh = new ModelActor("Stage", "Environment/Ground.mv1");
		AddChild(m_mesh);
	}

	int GetFrameIndex()
	{
		return FrameIndex;
	}
};