#include "Bullet.h"
#include "BulletData.h"
#include "BulletStatus.h"
#include "Character.h"
#include "Effect.h"
#include "SoundManager.h"
#include "CircleCollider.h"
#include "Time.h"
#include "Lerp.h"

//コンストラクタ
Bullet::Bullet(
	const char* filePath,
	const Vector3& position,
	const Vector3& forward,
	Stage* stage,
	int bulletIndex
) :
	ModelActor("Bullet", filePath, position),
	m_stage(stage),
	m_forward(forward),
	m_elapsedTime(0.0f),
	m_bulletStatus(nullptr)
{
	//弾のステータスを取得
	BulletData data;
	m_bulletStatus = data.GetBulletData(bulletIndex);

	m_reflectAmount = m_bulletStatus->reflectAmount;
	m_addForce = m_bulletStatus->addForce;
	m_power = m_bulletStatus->power;
	m_aliveTime = m_bulletStatus->aliveTime;
	m_size = m_bulletStatus->size;

	//姿勢情報
	m_transform.scale = m_size;

	//衝突判定
	m_collider = new CircleCollider(m_size);

	//エフェクト
	m_effect = new Effect("Resource/Effect/bullet.efk", 10, 700);
	m_effect->Play();
}

//更新
void Bullet::Update()
{
	//本来の更新
	ModelActor::Update();

	//移動前の座標
	Vector3 prevPos = m_transform.position;

	//生存時間を過ぎていたら削除
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= m_aliveTime) Destroy();

	//移動前の床情報を取得
	MV1_COLL_RESULT_POLY prevPoly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		prevPos + Vector3(0, 100, 0),
		prevPos - Vector3(0, 100, 0));

	//自身の正面に移動
	m_transform.position += m_forward.Normalized() * m_addForce * Time::GetInstance()->GetDeltaTime();

	//移動後の床情報を取得
	MV1_COLL_RESULT_POLY poly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		m_transform.position + Vector3(0, 100, 0),
		m_transform.position - Vector3(0, 100, 0));

	//床を踏み外している？
	if (!poly.HitFlag)
	{
		int index = 0;
		while (index < 3)
		{
			//床ポリゴンの三角形のうち、どの辺を跨いでいるかを調べる
			int toIndex = index + 1 != 3 ? index + 1 : 0;

			//線分同士の交差判定
			Vector2 a(prevPos.x, prevPos.z);
			Vector2 b(m_transform.position.x, m_transform.position.z);
			Vector2 c(prevPoly.Position[index].x, prevPoly.Position[index].z);
			Vector2 d(prevPoly.Position[toIndex].x, prevPoly.Position[toIndex].z);

			Vector2 ab = b - a;
			Vector2 cd = d - c;
			Vector2 ca = a - c;

			index++;

			//線分が平行？
			if (Vector2::Cross(cd, ab) == 0) continue;

			//線分同士の交差点を計算
			//tが0～1の間であれば線分同士が交差している
			float t = Vector2::Cross(-cd, ca) / Vector2::Cross(cd, ab);
			if (t < 0 || 1 < t)
			{
				continue;
			}

			//交差座標を計算
			Vector2 crossPos = Lerp::Exec(a, b, t);

			//移動後の座標から交差した辺の最近点を計算
			Vector2 cpcN = (c - crossPos).Normalize();
			Vector2 x = crossPos + (cpcN * Vector2::Dot(cpcN, b - crossPos));

			//垂直に接触したなら自身の正面ベクトルを反転
			if (static_cast<int>(crossPos.x) == static_cast<int>(crossPos.y))
			{
				m_forward = -m_forward;
			}

			//接触した面を算出し、反転させる
			if (crossPos == x) m_forward *= -1;
			else if (crossPos.x == x.x) m_forward.x *= -1;
			else m_forward.z *= -1;

			// 調整後の座標でも床に乗れない場合は移動をなかったことにする
			if (!MV1CollCheck_Line(
				m_stage->GetModelHandle(),
				m_stage->GetFrameIndex(),
				m_transform.position + Vector3(0, 100, 0),
				m_transform.position - Vector3(0, 100, 0)).HitFlag)
			{
				m_transform.position = prevPos;
			}

			//反射可能回数の減算
			m_reflectAmount--;

			//体力が無ければ削除
			if (m_reflectAmount <= 0) Destroy();
		}
	}
}

//衝突イベント
void Bullet::OnCollision(const ModelActor* other)
{
	if (other->GetName() == "Player")
	{
		//自分の親ならダメージを与えない
		if (GetParent() == other) return;

		//効果音再生
		SoundManager::Play("Resource/Sound/se_damage.mp3");

		//他プレイヤーと衝突したらダメージを与える
		dynamic_cast<Character*>(const_cast<ModelActor*>(other))->Damage(m_power);
		Destroy();
	}
}