#pragma once
#include "LoaderBase.h"

//3D���f�����[�_�[�N���X
class ModelLoader : public LoaderBase
{
private:
	ModelLoader() {}

protected:
	virtual int LoadResource(const char* path) override;
	virtual void DeleteResource(int id) override;

public:
	//�V���O���g��
	static ModelLoader* GetInstance()
	{
		static ModelLoader instance;
		return &instance;
	}
};