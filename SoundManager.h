#pragma once
#include "DxLib.h"
#include "SoundLoader.h"

struct SoundManager
{
private:
	static constexpr int Volume = 50;

public:
	//���ʉ��̍Đ�
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

	//���ʂ̒���
	static void SetVolume(int id)
	{
		ChangeVolumeSoundMem(Volume, id);
	}

	//���̒�~
	static void SoundStop(int id)
	{
		StopSoundMem(id);
	}
};