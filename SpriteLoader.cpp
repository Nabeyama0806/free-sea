#include "SpriteLoader.h"
#include "DxLib.h"

int SpriteLoader::LoadResource(const char* path)
{
	return LoadGraph(path);
}

void SpriteLoader::DeleteResource(int id)
{
	DeleteGraph(id);
}