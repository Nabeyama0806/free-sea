#include "Bullet.h"
#include "Stage.h"
#include "Effect.h"
#include "CircleCollider.h"
#include "Time.h"
#include "Lerp.h"

//�R���X�g���N�^
Bullet::Bullet(const Vector3& position, const Vector3& forward, Stage* stage, int maxHelath, int powar, float addForce, float size) :
	ModelActor("Bullet", nullptr, position),
	m_stage(stage),
	m_forward(forward),
	m_health(maxHelath),
	m_powar(powar),
	m_addForce(addForce),
	m_elapsedTime(0)
{
	//���f��
	m_model = new Model("Resource/Model/Bullet.mv1");

	//�����蔻��
	m_collider = new CircleCollider(Scale, Vector3(1, 8, -7));

	//�p�����
	m_transform.scale = size;
	m_effectOffset = Vector3(0, -25, -10);

	//�G�t�F�N�g
	m_effect = new Effect("Resource/Effect/bullet.efk", 10, 700);

	//�G�t�F�N�g�̍Đ�
	m_effect->Play();
}

//�X�V
void Bullet::Update()
{
	//�{���̍X�V
	ModelActor::Update();

	//�ړ��O�̍��W
	Vector3 prevPos = m_transform.position;

	//�̗͂�������΍폜
	if (m_health <= 0) Destroy();

	//�������Ԃ��߂��Ă�����폜
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime >= EraseTime) Destroy();

	//�ړ��O�̏������擾
	MV1_COLL_RESULT_POLY prevPoly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		prevPos + Vector3(0, 100, 0),
		prevPos - Vector3(0, 100, 0));

	//���g�̐��ʂɈړ�
	m_transform.position += m_forward.Normalized() * m_addForce * Time::GetInstance()->GetDeltaTime();

	//�ړ���̏������擾
	MV1_COLL_RESULT_POLY poly = MV1CollCheck_Line(
		m_stage->GetModelHandle(),
		m_stage->GetFrameIndex(),
		m_transform.position + Vector3(0, 100, 0),
		m_transform.position - Vector3(0, 100, 0));

	//���𓥂݊O���Ă���H
	if (!poly.HitFlag)
	{
		int index = 0;
		while (index < 3)
		{
			//���|���S���̎O�p�`�̂����A�ǂ̕ӂ��ׂ��ł��邩�𒲂ׂ�
			int toIndex = index + 1 != 3 ? index + 1 : 0;

			//�������m�̌�������
			Vector2 a(prevPos.x, prevPos.z);
			Vector2 b(m_transform.position.x, m_transform.position.z);
			Vector2 c(prevPoly.Position[index].x, prevPoly.Position[index].z);
			Vector2 d(prevPoly.Position[toIndex].x, prevPoly.Position[toIndex].z);

			Vector2 ab = b - a;
			Vector2 cd = d - c;
			Vector2 ca = a - c;

			index++;

			//���������s�H
			if (Vector2::Cross(cd, ab) == 0) continue;

			//�������m�̌����_���v�Z
			//t��0�`1�̊Ԃł���ΐ������m���������Ă���
			float t = Vector2::Cross(-cd, ca) / Vector2::Cross(cd, ab);
			if (t < 0 || 1 < t) continue;

			//�������W���v�Z
			Vector2 crossPos = Lerp::Exec(a, b, t);

			//�ړ���̍��W������������ӂ̍ŋߓ_���v�Z
			Vector2 cpcN = (c - crossPos).Normalize();
			Vector2 x = crossPos + (cpcN * Vector2::Dot(cpcN, b - crossPos));

			//X�����������Ȃ牡���ɐڐG���Ă��邽�߁AX���𔽓]
			crossPos.x == x.x ? m_forward.x *= -1 : m_forward.z *= -1;

			//���ˌ�̓T�C�Y������������
			m_transform.scale -= 4;

			//���ˉ\�񐔂̌��Z
			m_health--;
		}
	}
}