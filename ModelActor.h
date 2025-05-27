#pragma once
#include "ActorBase.h"
#include "Transform.h"
#include <string>

class Model;

class ModelActor : public ActorBase
{
protected:
	static constexpr Vector3 ColliderSize = Vector3(100, 100, 100);			// コライダーのサイズ
	static constexpr Vector3 Scale = Vector3(25, 25, 25);
	
	Model* m_model;	//3Dモデル	

	virtual void Load() override;		//リソースの読み込み
	virtual void Release() override;	//リソースの解放
	virtual void Draw() override;		//描画
	virtual void OnDestroy();			//オブジェクトの削除

public:
	//コンストラクタ
	ModelActor(
		const char* name,
		const char* modelFileName = nullptr,
		const Vector3& position = Vector3()
	);

	//子ノードを含む更新
	virtual void TreeUpdate() override;

	//衝突イベント
	virtual void OnCollision(const ModelActor* other) {}
};