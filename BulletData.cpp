#include "BulletData.h"
#include <fstream>
#include <sstream>

//CSV�t�@�C������e�f�[�^��ǂݍ���
bool BulletData::LoadCSV(const std::string& filePath)
{
    std::ifstream file(filePath);
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
        m_idToIndex[data.id] = m_bulletList.size();
        m_nameToIndex[data.name] = m_bulletList.size();
        m_bulletList.push_back(data);
    }
    return true;
}

//ID�Œe�f�[�^���擾
const BulletStatus* BulletData::GetBulletData(int id) const
{
    auto it = m_idToIndex.find(id);
    return it == m_idToIndex.end() ? nullptr : &m_bulletList[it->second];
}

//���O�Œe�f�[�^���擾
const BulletStatus* BulletData::GetBulletData(const std::string& name) const
{
    auto it = m_nameToIndex.find(name);
	return it == m_nameToIndex.end() ? nullptr : &m_bulletList[it->second];
}
