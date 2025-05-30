#include "Bullet.h"
#include "Player.h"
#include "Effect.h"
#include "Time.h"

//コンストラクタ
Bullet::Bullet(const Vector3& position, const Vector3& forward, Player* player) :
ModelActor("Bullet", nullptr, position),
m_player(player),
m_forward(forward),
m_elapsedTime(0)
{
	//モデル
	m_model = new Model("Resource/Model/Bubble2.mv1");

	//エフェクト
	m_effect = new Effect("Resource/Effect/key.efk", 8, 700);

	//姿勢情報
	m_transform.scale = Scale;
	m_effectOffset = Vector3(0, -25, -8);

	//エフェクトの再生
	m_effect->Play(false);
}

//更新
void Bullet::Update()
{
	//本来の更新
	ModelActor::Update();

	//生存時間を過ぎていれば削除
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime > EraseTime)
	{
		m_effect->Stop();
		Destroy();
	}

	//投げる
	m_transform.position += Shot(m_forward);

}

//発射
Vector3 Bullet::Shot(Vector3& position) const
{
	//正面に飛ばす
	return position.Normalized() * AddForce * Time::GetInstance()->GetDeltaTime();
}