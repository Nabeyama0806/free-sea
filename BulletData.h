#pragma once
#include "Vector3.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <unordered_map>

// �e�f�[�^�\����
struct DataBase
{
    int id;
    std::string name;
    int health;
    int power;
    float addForce;
    float size;
    float eraseTime;
};

// �e�f�[�^�Ǘ��N���X
class BulletData
{
public:
    // CSV�t�@�C������e�f�[�^��ǂݍ���
    bool LoadCSV(const std::string& filePath);

    // ID�Œe�f�[�^���擾
    const DataBase* GetBulletData(int id) const;

    // ���O�Œe�f�[�^���擾
    const DataBase* GetBulletData(const std::string& name) const;

    // �S�e�f�[�^�擾
    const std::vector<DataBase>& GetAll() const 
    { 
        return m_bulletList; 
    }

private:
	// �e�f�[�^�̃��X�g
    std::vector<DataBase> m_bulletList;

	//ID�Ɩ��O����C���f�b�N�X���}�b�s���O����n�b�V���e�[�u��
    std::unordered_map<int, size_t> m_idToIndex;
    std::unordered_map<std::string, size_t> m_nameToIndex;
};
