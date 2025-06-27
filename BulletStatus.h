#pragma once
#include <string>

//�e�f�[�^�̃X�e�[�^�X���Ǘ�����\����
struct BulletStatus
{
public:
	int id;                 //���ʔԍ�
	std::string name;		//���O
	int bulletAmount;		//���Ŕ��˂����e�̐�
	float shotCoolTime;		//���ˊԊu
	float shotRate;			//�e�Ԃ̔��ˊԊu
	int diffusionAmount;	//�g�U�e�̐�
	float diffusionAngle;	//�g�U�e�̊p�x
	int reflectAmount;		//���ˉ�
	float addForce;			//�������
	int power;				//�U����
	float aliveTime;		//��������(�b)
	float size;				//�傫��
	float mass;				//�d��(�ړ����x�ɉe��)

public:
	//�R���X�g���N�^
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
