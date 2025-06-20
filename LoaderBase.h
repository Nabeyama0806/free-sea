#pragma once
#include <unordered_map>
#include "LoadData.h"

//���� : ���ۃN���X�̓I�u�W�F�N�g�����Ȃ�(�|�C���^�͍���)

//���\�[�X�̊�ꃍ�[�_�[�N���X(���ۃN���X)
class LoaderBase
{
protected:
	const char* RootPath = "Resource/";
	std::unordered_map<const char*, LoadData> m_dataList;	//���\�[�X�ꗗ

#ifdef _DEBUG
	static const int FontSize = 10;
	static const int FontThick = 3;
	static const int FontMargin = 2;
	int m_fontHandle;
#endif

	LoaderBase();
	virtual ~LoaderBase();

	virtual int LoadResource(const char* path) = 0;	//���\�[�X�̓ǂݍ���
	virtual void DeleteResource(int id) = 0;		//���\�[�X�̔j��

public:
	virtual int Load(const char* path);	//���\�[�X�̓ǂݍ���
	virtual void Delete(const char* path);	//���\�[�X�̔j��

#ifdef _DEBUG
	void Draw();
#endif
};