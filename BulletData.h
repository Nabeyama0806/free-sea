#pragma once
#include "BulletStatus.h"
#include "Vector3.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <unordered_map>

// �e�f�[�^�Ǘ��N���X
class BulletData
{
private:
    //�e�f�[�^�̃��X�g
	std::vector<BulletStatus> m_bulletList;     

	//ID�Ɩ��O����C���f�b�N�X���Ǘ�
    std::unordered_map<int, size_t> m_idToIndex;
    std::unordered_map<std::string, size_t> m_nameToIndex;

public:
    // CSV�t�@�C������e�f�[�^��ǂݍ���
    bool LoadCSV(const std::string& filePath);

    // ID�Œe�f�[�^���擾
    const BulletStatus* GetBulletData(int id) const;

    // ���O�Œe�f�[�^���擾
    const BulletStatus* GetBulletData(const std::string& name) const;

    // �S�e�f�[�^�擾
    const std::vector<BulletStatus>& GetAll() const
    {
        return m_bulletList;
    }
};
