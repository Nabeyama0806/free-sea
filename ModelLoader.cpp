#include "ModelLoader.h"
#include "DxLib.h"

//リソースの読み込み
int ModelLoader::Load(const char* path)
{
	LoadData* loadData = nullptr;

	//既に読み込んでいるかをチェック
	auto data = m_dataList.find(path);
	if (data != m_dataList.end())
	{
		//読み込み済みのデータで処理をする
		loadData = &data->second;
	}
	else
	{
		//新規ロード
		int id = LoadResource(path);

		//登録
		auto result = m_dataList.emplace(path, LoadData(id));

		//登録したデータで処理する
		loadData = &result.first->second;
	}

	//読み込みカウントを増やす
	loadData->count++;

	return loadData->id;
}

//リソースの破棄
void ModelLoader::Delete(int id)
{
	LoadData* loadData = nullptr;

	//モデルハンドルのファイルパスを取得
	auto data = m_modelDataList.find(id);

	//読み込んでいなかったので何もしない
	if (data == m_modelDataList.end()) return;

	//読み込みカウントを減らす
	

	//読み込みカウントが0になったら破棄する
	if (loadData->count <= 0)
	{
		//破棄
		DeleteResource(loadData->id);

		//一覧からも削除
		//m_dataList.erase();
	}
}

int ModelLoader::LoadResource(const char* path)
{
	return MV1DuplicateModel(MV1LoadModel(path));
}

void ModelLoader::DeleteResource(int id)
{
	MV1DeleteModel(id);
}