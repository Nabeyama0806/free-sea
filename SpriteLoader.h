#pragma once
#include "LoaderBase.h"

//�摜���[�_�[�N���X
class SpriteLoader : public LoaderBase
{
private:
	SpriteLoader() {}

protected:
	virtual int LoadResource(const char* path) override;
	virtual void DeleteResource(int id) override;

public:
	//�V���O���g��
	static SpriteLoader* GetInstance()
	{
		static SpriteLoader instance;
		return &instance;
	}
};