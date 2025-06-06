#include "Bullet.h"
#include "Stage.h"
#include "Effect.h"
#include "CircleCollider.h"
#include "Time.h"
#include "Lerp.h"

//コンストラクタ
Bullet::Bullet(const Vector3& position, const Vector3& forward, Stage* stage, int maxHelath, int powar, float addForce, float size) :
	ModelActor("Bullet", nullptr, position),
	m_stage(stage),
	m_forward(forward),
	m_health(maxHelath),
	m_powar(powar),
	m_addForce(addForce),
	m_elapsedTime(0)
{
	//モデル
	m_model = new Model("Resource/Model/Bullet.mv1");

	//当たり判定
	m_collider = new CircleCollider(Scale, Vector3(1, 8, -7));

	//姿勢情報
	m_transform.scale = size;
	m_effectOffset = Vector3(0, -25, -10);

	//エフェクト
	m_effect = new Effect("Resource/Effect/bullet.efk", 10, 700);

	//エフェクトの再生
	m_effect->Play();
}

//更新
void Bullet::Update()
{
	//本来の更新
	ModelActor::Update();

	//移動前の座標
	Vector3 prevPos = m_transform.position;

	//体力が無ければ削除
	if (m_health <= 0) Destroy();

	//生存時間を過ぎていたら削除
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= EraseTime) Destroy();

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
			if (t < 0 || 1 < t) continue;

			//交差座標を計算
			Vector2 crossPos = Lerp::Exec(a, b, t);

			//移動後の座標から交差した辺の最近点を計算
			Vector2 cpcN = (c - crossPos).Normalize();
			Vector2 x = crossPos + (cpcN * Vector2::Dot(cpcN, b - crossPos));

			//X軸が等しいなら横軸に接触しているため、X軸を反転
			crossPos.x == x.x ? m_forward.x *= -1 : m_forward.z *= -1;

			//反射後はサイズを小さくする
			m_transform.scale -= 4;

			//反射可能回数の減算
			m_health--;
		}
	}
}