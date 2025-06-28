#pragma once
#include "BulletStatus.h"
#include "Vector3.h"
#include "DxLib.h"
#include <string>
#include <vector>

// �e�f�[�^�Ǘ��N���X
class BulletData
{
private:
	const char* FilePath = "Resource/Data/BulletDataTable.csv"; //�e�f�[�^��CSV�t�@�C���p�X

    //�e�f�[�^�̃��X�g
	std::vector<BulletStatus*> m_bulletList;

public:
    //�V���O���g��
    static BulletData* GetInstance()
    {
        static BulletData instance;
        return &instance;
    }

    // CSV�t�@�C������e�f�[�^��ǂݍ���
    bool LoadCSV();

    // ID�Œe�f�[�^���擾
    BulletStatus* GetBulletData(int id)
    {
        return m_bulletList[id];
    }

    //�S�e�f�[�^�̐����擾
    const int GetBulletListSize() const
    {
        return static_cast<int>(m_bulletList.size());
    }

    //�S�e�f�[�^�擾
    const std::vector<BulletStatus*>& GetAll() const
    {
        return m_bulletList;
    }
};
