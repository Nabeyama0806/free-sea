#pragma once
#include <string>

//’eƒf[ƒ^‚ÌƒXƒe[ƒ^ƒX‚ğŠÇ—‚·‚é\‘¢‘Ì
struct BulletStatus
{
	int id;                 //¯•Ê”Ô†
	std::string name;		//–¼‘O
	int bulletAmount;		//ˆê‰ñ‚Å”­Ë‚³‚ê‚é’e‚Ì”
	float shotCoolTime;		//”­ËŠÔŠu
	float shotRate;			//’eŠÔ‚Ì”­ËŠÔŠu
	int diffusionAmount;	//ŠgU’e‚Ì”
	float diffusionAngle;	//ŠgU’e‚ÌŠp“x
	int reflectAmount;		//”½Ë‰ñ”
	float addForce;			//“Š‚°‚é—Í
	int power;				//UŒ‚—Í
	float aliveTime;		//¶‘¶ŠÔ(•b)
	float size;				//‘å‚«‚³
	float mass;				//d‚³(ˆÚ“®‘¬“x‚É‰e‹¿)
};
