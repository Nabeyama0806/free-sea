#pragma once
#include "BulletStatus.h"
#include "Vector3.h"
#include "DxLib.h"
#include <string>
#include <vector>

// 弾データ管理クラス
class BulletData
{
private:
	const char* FilePath = "Resource/Data/BulletDataTable.csv"; //弾データのCSVファイルパス

    //弾データのリスト
	std::vector<BulletStatus*> m_bulletList;

public:
    //シングルトン
    static BulletData* GetInstance()
    {
        static BulletData instance;
        return &instance;
    }

    // CSVファイルから弾データを読み込む
    bool LoadCSV();

    // IDで弾データを取得
    BulletStatus* GetBulletData(int id)
    {
        return m_bulletList[id];
    }

    //全弾データの数を取得
    const int GetBulletListSize() const
    {
        return static_cast<int>(m_bulletList.size());
    }

    //全弾データ取得
    const std::vector<BulletStatus*>& GetAll() const
    {
        return m_bulletList;
    }
};
