#pragma once
#pragma once
#include "Bullet.h"
#include "Stage.h"

class DiffusionBullet : public Bullet
{
private:
	static constexpr int MaxHealth = 1;			//”½Ë‚Å‚«‚é‰ñ”(‘Ì—Í)
	static constexpr int Power = 15;			//UŒ‚—Í
	static constexpr float AddForce = 550.0f;	//“Š‚°‚é—Í
	static constexpr float Size = 20.0f;		//‘å‚«‚³‚Ì’²®
	static constexpr float EraseTime = 0.8f;	//¶‘¶ŠÔ(•b)

public:
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	DiffusionBullet(const char* modelFilePath, const Vector3& position, const Vector3& forward, Stage* stage) :
		Bullet(modelFilePath, position, forward, stage, Size)
	{
		//’e‚ÌƒXƒe[ƒ^ƒX‚ğİ’è
		m_health = MaxHealth;
		m_power = Power;
		m_addForce = AddForce;
		m_eraseTime = EraseTime;
	}

	static constexpr int BulletAmount = 2;				//ˆê‰ñ‚Å”­Ë‚³‚ê‚é’e‚Ì”
	static constexpr float ShotCoolTime = 0.8f;			//”­ËŠÔŠu
	static constexpr float BulletFiringRate = 0.2f;		//’eŠÔ‚Ì”­ËŠÔŠu

	static constexpr int DiffusionBulletAmount = 3;		//ŠgU’e‚Ì”
	static constexpr float AngleRate = 6.0f;			//ŠgU’e‚ÌŠp“x
};