#pragma once
#include "Vector3.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <unordered_map>

// 弾データ構造体
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

// 弾データ管理クラス
class BulletData
{
public:
    // CSVファイルから弾データを読み込む
    bool LoadCSV(const std::string& filePath);

    // IDで弾データを取得
    const DataBase* GetBulletData(int id) const;

    // 名前で弾データを取得
    const DataBase* GetBulletData(const std::string& name) const;

    // 全弾データ取得
    const std::vector<DataBase>& GetAll() const 
    { 
        return m_bulletList; 
    }

private:
	// 弾データのリスト
    std::vector<DataBase> m_bulletList;

	//IDと名前からインデックスをマッピングするハッシュテーブル
    std::unordered_map<int, size_t> m_idToIndex;
    std::unordered_map<std::string, size_t> m_nameToIndex;
};
