#pragma once
#include "BulletStatus.h"
#include "Vector3.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <unordered_map>

// 弾データ管理クラス
class BulletData
{
private:
    //弾データのリスト
	std::vector<BulletStatus> m_bulletList;     

	//IDと名前からインデックスを管理
    std::unordered_map<int, size_t> m_idToIndex;
    std::unordered_map<std::string, size_t> m_nameToIndex;

public:
    // CSVファイルから弾データを読み込む
    bool LoadCSV(const std::string& filePath);

    // IDで弾データを取得
    const BulletStatus* GetBulletData(int id) const;

    // 名前で弾データを取得
    const BulletStatus* GetBulletData(const std::string& name) const;

    // 全弾データ取得
    const std::vector<BulletStatus>& GetAll() const
    {
        return m_bulletList;
    }
};
