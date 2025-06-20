#pragma once
#include "CharacterBase.h"

class PinkBird : public CharacterBase
{
private:
	static constexpr int Health = 230;
	static constexpr int BulletAmount = 2;				//ˆê‰ñ‚Å”­Ë‚³‚ê‚é’e‚Ì”
	static constexpr float ShotCoolTime = 1.0f;			//”­ËŠÔŠu
	static constexpr float BulletFiringRate = 0.3f;		//’eŠÔ‚Ì”­ËŠÔŠu

	void BulletShot();		//”­Ë
	bool BulletInstance();	//’e‚Ì¶¬

protected:
	virtual void Update() override;			//XV
	virtual void Draw() override;

public:
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	PinkBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex);
};