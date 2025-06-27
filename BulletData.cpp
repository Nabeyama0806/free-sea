#include "BulletData.h"
#include <fstream>
#include <sstream>

//CSV�t�@�C������e�f�[�^��ǂݍ���
bool BulletData::LoadCSV()
{
    std::ifstream file(FilePath);
    if (!file.is_open()) return false;

    //�w�b�_�[�s���X�L�b�v
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) 
    {
		//�s����̏ꍇ�̓X�L�b�v
		if (line.empty()) continue;

        std::istringstream ss(line);
        BulletStatus data;
        std::string token;

		//�ǂݍ���
        std::getline(ss, token, ','); data.id = std::stoi(token);
        std::getline(ss, token, ','); data.name = token;
		std::getline(ss, token, ','); data.bulletAmount = std::stoi(token);
		std::getline(ss, token, ','); data.shotCoolTime = std::stof(token);
		std::getline(ss, token, ','); data.shotRate = std::stof(token);
		std::getline(ss, token, ','); data.diffusionAmount = std::stoi(token);
		std::getline(ss, token, ','); data.diffusionAngle = std::stof(token);
		std::getline(ss, token, ','); data.reflectAmount = std::stoi(token);
		std::getline(ss, token, ','); data.addForce = std::stof(token);
		std::getline(ss, token, ','); data.power = std::stoi(token);
		std::getline(ss, token, ','); data.aliveTime = std::stof(token);
		std::getline(ss, token, ','); data.size = std::stof(token);
		std::getline(ss, token, ','); data.mass = std::stof(token);

		//�f�[�^�����X�g�ɒǉ�
        m_bulletList.push_back(data);
    }
    return true;
}
