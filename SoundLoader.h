#pragma once
#include "LoaderBase.h"

//画像ローダークラス
class SoundLoader : public LoaderBase
{
private:
	SoundLoader() {}

protected:
	virtual int LoadResource(const char* path) override;
	virtual void DeleteResource(int id) override;

public:
	//シングルトン
	static SoundLoader* GetInstance()
	{
		static SoundLoader instance;
		return &instance;
	}
};