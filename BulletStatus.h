#pragma once
#include <string>

//�e�f�[�^�̃X�e�[�^�X���Ǘ�����\����
struct BulletStatus
{
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
};
