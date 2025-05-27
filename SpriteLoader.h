#pragma once
#include "LoaderBase.h"

//画像ローダークラス
class SpriteLoader : public LoaderBase
{
private:
	SpriteLoader() {}

protected:
	virtual int LoadResource(const char* path) override;
	virtual void DeleteResource(int id) override;

public:
	//シングルトン
	static SpriteLoader* GetInstance()
	{
		static SpriteLoader instance;
		return &instance;
	}
};