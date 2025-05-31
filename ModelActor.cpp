#include "ModelActor.h"
#include "ModelAnimation.h"
#include "ModelActorCollision.h"
#include "Model.h"
#include "Effect.h"

//コンストラクタ
ModelActor::ModelActor(const char* name, const char* modelFileName, const Vector3& position) :
	ActorBase(name, modelFileName, position), 
	m_model(nullptr),
	m_collider(nullptr),
	m_effect(nullptr)
{
	//ファイルパスが指定されていればロードする
	if (modelFileName)
	{
		m_model = new Model(modelFileName);
	}
}

//リソースの読み込み
void ModelActor::Load()
{
	//モデル
	if (m_model)
	{
		m_model->Load();
	}

	//衝突判定の追加
	if (m_collider)
	{
		ModelActorCollision::GetInstance()->Register(this);
	}
}

//リソースの解放
void ModelActor::Release()
{
	//モデル
	if (m_model)
	{
		delete m_model;
		m_model = nullptr;
	}
	
	//衝突判定から除外
	if (m_collider)
	{
		ModelActorCollision::GetInstance()->Remove(this);
		delete m_collider;
		m_collider = nullptr;
	}

	//破棄処理
	OnDestroy();
}

//描画
void ModelActor::Draw()
{
	//モデル
	if (m_model)
	{
		m_model->Draw(m_transform);
	}

	//当たり判定
	if (m_collider)
	{
		m_collider->Draw(m_transform);
	}

}

//子ノードを含む更新
void ModelActor::TreeUpdate()
{
	//本来のUpdate
	Node::TreeUpdate();
	
	//モデル
	if (m_model)
	{
		m_model->Update();
	}

	//エフェクト
	if (m_effect)
	{
		m_effect->Update(m_transform.position + m_effectOffset);
	}
}

//破棄処理
void ModelActor::OnDestroy()
{
	//エフェクトの停止
	if (m_effect)
	{
		m_effect->Stop();
	}
}