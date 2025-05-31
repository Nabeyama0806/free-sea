#pragma once
#include <list>

//クラスの前方宣言
class ModelActor;

//Actor同士の接触判定クラス
class ModelActorCollision
{
private:
	std::list<ModelActor*> m_actorList;	//衝突判定をするActorのリスト

	//コンストラクタ
	ModelActorCollision() {}

public:
	//シングルトン
	static ModelActorCollision* GetInstance()
	{
		static ModelActorCollision instance;
		return &instance;
	}

	//登録
	void Register(ModelActor* actor)
	{
		m_actorList.push_back(actor);
	}

	//削除
	void Remove(ModelActor* actor)
	{
		m_actorList.remove(actor);
	}

	//更新
	void Update();

#ifdef _DEBUG
	//描画
	void Draw() const;
#endif
};