#include "SoundLoader.h"
#include "DxLib.h"

int SoundLoader::LoadResource(const char* path)
{
	return LoadSoundMem(path);
}

void SoundLoader::DeleteResource(int id)
{
	DeleteSoundMem(id);
}