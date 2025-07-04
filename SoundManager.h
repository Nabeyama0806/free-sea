#pragma once
#include "DxLib.h"
#include "SoundLoader.h"

struct SoundManager
{
private:
	static constexpr int Volume = 180;

public:
	//効果音の読み込み
	static int Load(const char* path)
	{
		return SoundLoader::GetInstance()->Load(path);
	}

	//効果音の再生
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

	//音量の調整
	static void SetVolume(int id)
	{
		ChangeVolumeSoundMem(Volume, id);
	}

	//音の停止
	static void SoundStop(int id)
	{
		StopSoundMem(id);
	}
};