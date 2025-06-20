#pragma once
#include "LoaderBase.h"
#include <unordered_map>

//3Dモデルローダークラス
class ModelLoader : public LoaderBase
{
private:
	//<int : モデルハンドル(Dupe), char* : モデルのファイルパス>
	std::unordered_map<int, const char*> m_modelDataList;	//リソースの逆引き

	ModelLoader() {}
	virtual void Delete(const char* path) override {};	//リソースの破棄

protected:
	virtual int LoadResource(const char* path) override;
	virtual void DeleteResource(int id) override;

public:
	//シングルトン
	static ModelLoader* GetInstance()
	{
		static ModelLoader instance;
		return &instance;
	}

	virtual int Load(const char* path) override;	//リソースの読み込み
	void Delete(int id);
};