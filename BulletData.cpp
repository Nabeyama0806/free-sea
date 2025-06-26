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
        std::istringstream ss(line);
        DataBase data;
        std::string token;

		//�ǂݍ���
        std::getline(ss, token, ','); data.id = std::stoi(token);
        std::getline(ss, token, ','); data.name = token;
        std::getline(ss, token, ','); data.health = std::stoi(token);
        std::getline(ss, token, ','); data.power = std::stoi(token);
        std::getline(ss, token, ','); data.addForce = std::stof(token);
        std::getline(ss, token, ','); data.size = std::stof(token);
        std::getline(ss, token, ','); data.eraseTime = std::stof(token);

        m_idToIndex[data.id] = m_bulletList.size();
        m_nameToIndex[data.name] = m_bulletList.size();
        m_bulletList.push_back(data);
    }
    return true;
}

//ID�Œe�f�[�^���擾
const DataBase* BulletData::GetBulletData(int id) const
{
    auto it = m_idToIndex.find(id);
    if (it != m_idToIndex.end()) 
    {
        return &m_bulletList[it->second];
    }
    return nullptr;
}

//���O�Œe�f�[�^���擾
const DataBase* BulletData::GetBulletData(const std::string& name) const
{
    auto it = m_nameToIndex.find(name);
    if (it != m_nameToIndex.end()) 
    {
        return &m_bulletList[it->second];
    }
    return nullptr;
}
