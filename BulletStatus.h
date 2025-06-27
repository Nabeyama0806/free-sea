#pragma once
#include <string>

//弾データのステータスを管理する構造体
struct BulletStatus
{
public:
	int id;                 //識別番号
	std::string name;		//名前
	int bulletAmount;		//一回で発射される弾の数
	float shotCoolTime;		//発射間隔
	float shotRate;			//弾間の発射間隔
	int diffusionAmount;	//拡散弾の数
	float diffusionAngle;	//拡散弾の角度
	int reflectAmount;		//反射回数
	float addForce;			//投げる力
	int power;				//攻撃力
	float aliveTime;		//生存時間(秒)
	float size;				//大きさ
	float mass;				//重さ(移動速度に影響)

public:
	//コンストラクタ
	BulletStatus() :
		id(0),
		name(""),
		bulletAmount(0),
		shotCoolTime(0.0f),
		shotRate(0.0f),
		diffusionAmount(0),
		diffusionAngle(0.0f),
		reflectAmount(0),
		addForce(0.0f), 
		power(0),
		aliveTime(0.0f),
		size(1.0f),
		mass(1.0f)
	{
	}
};
