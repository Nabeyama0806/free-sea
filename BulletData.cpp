#include "BulletData.h"
#include <fstream>
#include <sstream>

//CSVファイルから弾データを読み込む
bool BulletData::LoadCSV()
{
    std::ifstream file(FilePath);
    if (!file.is_open()) return false;

    //ヘッダー行をスキップ
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) 
    {
		//行が空の場合はスキップ
		if (line.empty()) continue;

        std::istringstream ss(line);
        BulletStatus data;
        std::string token;

		//読み込み
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

		//データをリストに追加
        m_bulletList.push_back(data);
    }
    return true;
}
