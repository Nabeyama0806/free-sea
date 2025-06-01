#include "Bullet.h"
#include "Player.h"
#include "CircleCollider.h"
#include "Effect.h"
#include "Time.h"

//コンストラクタ
Bullet::Bullet(const Vector3& position, const Vector3& forward, Player* player) :
	ModelActor("Bullet", nullptr, position),
	m_player(player),
	m_forward(forward),
	m_health(MaxHealth),
	m_elapsedTime(0)
{
	//モデル
	m_model = new Model("Resource/Model/Bubble2.mv1");

	//当たり判定
	m_collider = new CircleCollider(Scale + 5.0f, Vector3(1, 8, -7));

	//エフェクト
	m_effect = new Effect("Resource/Effect/bullet.efk", 10, 700);

	//姿勢情報
	m_transform.scale = Scale;
	m_effectOffset = Vector3(0, -25, -10);

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
	if (m_elapsedTime > EraseTime) Destroy();

	//投げる
	m_transform.position += m_forward.Normalized() * AddForce * Time::GetInstance()->GetDeltaTime();
}

//ModelActor同士の衝突イベント
void Bullet::OnCollision(const ModelActor* other)
{
	//当たり判定用のオブジェクトに衝突したら削除
	if (other->GetName() == "HitBox")
	{
		Destroy();
	}
}

//ステージとの衝突イベント
void Bullet::OnHitPolygon(const ColliderResult* result)
{
	//反射ベクトルを計算
	Vector3 reflected;
	Vector3::ReflectVector(&reflected, m_forward, result->Normal);
	m_forward = reflected.Normalized();

	//反射後、弾を少し法線方向にずらして多重反射を防ぐ
	m_transform.position += result->Normal * 1.0f;

	//体力を消費
	m_health--;
	if (m_health <= 0) Destroy();
}