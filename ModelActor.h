#pragma once
#include "ActorBase.h"
#include "Transform.h"
#include "Collider.h"
#include "Model.h"
#include <string>

class Model;
class Effect;

class ModelActor : public ActorBase
{
protected:
	static constexpr Vector3 ColliderSize = Vector3(100, 100, 100);	
	static constexpr Vector3 Scale = Vector3(25, 25, 25);
	
	Model* m_model;	
	Effect* m_effect;
	Collider* m_collider;
	Vector3 m_effectOffset;

	virtual void Load() override;		//リソースの読み込み
	virtual void Release() override;	//リソースの解放
	virtual void Draw() override;		//描画
	virtual void OnDestroy() override;	//オブジェクトの削除

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

	//衝突判定の形状を取得
	const Collider* GetCollider() const
	{
		return m_collider;
	}

	//モデルの識別番号を取得
	const int GetModelHandle()
	{
		return m_model->GetModelHandle();
	}
};