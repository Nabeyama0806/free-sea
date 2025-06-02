#pragma once
#include "ModelActor.h"

class Stage : public ModelActor
{
private:
	static constexpr int FrameIndex = -1;

	int m_modelHandle;

public:
	//�R���X�g���N�^
	Stage() :
		ModelActor("Stage", "Environment/Ground.mv1"),
		m_modelHandle(0)
	{

	}

	int GetFrameIndex()
	{
		return FrameIndex;
	}
};