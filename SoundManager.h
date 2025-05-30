#pragma once
#include "DxLib.h"
#include "SoundLoader.h"

struct SoundManager
{
private:
	static constexpr int Volume = 120;

public:
	//Œø‰Ê‰¹‚ÌÄ¶
	static void Play(int se, int type = DX_PLAYTYPE_BACK)
	{
		SetVolume(se);
		PlaySoundMem(se, type);
	}
	static int Play(const char* path, int type = DX_PLAYTYPE_BACK)
	{
		int se = SoundLoader::GetInstance()->Load(path);
		Play(se, type);
		return se;
	}

	//‰¹—Ê‚Ì’²®
	static void SetVolume(int id)
	{
		ChangeVolumeSoundMem(Volume, id);
	}

	//‰¹‚Ì’â~
	static void SoundStop(int id)
	{
		StopSoundMem(id);
	}
};