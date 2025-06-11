#pragma once
#include "CharacterBase.h"

class BlueBird : public CharacterBase
{
private:
	//’e
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 5;				//ˆê‰ñ‚Å”­Ë‚³‚ê‚é’e‚Ì”
	static constexpr float ShotCoolTime = 1.7f;			//”­ËŠÔŠu
	static constexpr float BulletFiringRate = 0.24f;	//’eŠÔ‚Ì”­ËŠÔŠu
	void BulletShot();		//”­Ë
	bool BulletInstance();	//’e‚Ì¶¬

protected:
	virtual void Update() override;			//XV

public:
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	BlueBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};