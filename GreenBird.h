#pragma once
#include "CharacterBase.h"

class GreenBird : public CharacterBase
{
private:
	static constexpr int Health = 170;
	static constexpr int BulletAmount = 2;				//ˆê‰ñ‚Å”­Ë‚³‚ê‚é’e‚Ì”
	static constexpr float ShotCoolTime = 1.0f;			//”­ËŠÔŠu
	static constexpr float BulletFiringRate = 0.3f;		//’eŠÔ‚Ì”­ËŠÔŠu

	void BulletShot();		//”­Ë
	bool BulletInstance();	//’e‚Ì¶¬

protected:
	virtual void Update() override;			//XV

public:
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	GreenBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};