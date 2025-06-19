#pragma once
#include "CharacterBase.h"

class RedBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 1;				//ˆê‰ñ‚Å”­Ë‚³‚ê‚é’e‚Ì”
	static constexpr float ShotCoolTime = 0.7f;			//”­ËŠÔŠu
	static constexpr float BulletFiringRate = 0.7f;	//’eŠÔ‚Ì”­ËŠÔŠu

	void BulletShot();		//”­Ë
	bool BulletInstance();	//’e‚Ì¶¬

protected:
	virtual void Update() override;			//XV

public:
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	RedBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};