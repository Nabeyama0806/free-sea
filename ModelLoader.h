#pragma once
#include "LoaderBase.h"
#include <unordered_map>

//3D���f�����[�_�[�N���X
class ModelLoader : public LoaderBase
{
private:
	//<int : ���f���n���h��(Dupe), char* : ���f���̃t�@�C���p�X>
	std::unordered_map<int, const char*> m_modelDataList;	//���\�[�X�̋t����

	ModelLoader() {}
	virtual void Delete(const char* path) override {};	//���\�[�X�̔j��

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

	virtual int Load(const char* path) override;	//���\�[�X�̓ǂݍ���
	void Delete(int id);
};