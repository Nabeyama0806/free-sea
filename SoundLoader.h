#pragma once
#include "LoaderBase.h"

//�摜���[�_�[�N���X
class SoundLoader : public LoaderBase
{
private:
	SoundLoader() {}

protected:
	virtual int LoadResource(const char* path) override;
	virtual void DeleteResource(int id) override;

public:
	//�V���O���g��
	static SoundLoader* GetInstance()
	{
		static SoundLoader instance;
		return &instance;
	}
};