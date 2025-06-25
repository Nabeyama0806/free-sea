#pragma once
#include "ModelActor.h"

class Stage : public ModelActor
{
private:
	static constexpr int FrameIndex = -1;

	ModelActor* m_model;
	int m_modelHandle;

public:
	//�R���X�g���N�^
	Stage() :
		ModelActor("StageMesh", "Environment/Panel_Mesh.mv1"),
		m_model(nullptr),
		m_modelHandle(0)
	{
		//�����ڂ̃��f����ǂݍ���
		AddChild(new ModelActor("Stage", "Environment/Panel.mv1"));
	}

	int GetFrameIndex()
	{
		return FrameIndex;
	}
};