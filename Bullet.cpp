#include "Bullet.h"
#include "Player.h"
#include "CircleCollider.h"
#include "Effect.h"
#include "Time.h"

//�R���X�g���N�^
Bullet::Bullet(const Vector3& position, const Vector3& forward, Player* player) :
ModelActor("Bullet", nullptr, position),
m_player(player),
m_forward(forward),
m_elapsedTime(0)
{
	//���f��
	m_model = new Model("Resource/Model/Bubble2.mv1");

	//�����蔻��
	m_collider = new CircleCollider(Scale + 5.0f, Vector3(1, 8, -7));

	//�G�t�F�N�g
	m_effect = new Effect("Resource/Effect/bullet.efk", 10, 700);

	//�p�����
	m_transform.scale = Scale;
	m_effectOffset = Vector3(0, -25, -10);

	//�G�t�F�N�g�̍Đ�
	m_effect->Play(false);
}

//�X�V
void Bullet::Update()
{
	//�{���̍X�V
	ModelActor::Update();

	//�������Ԃ��߂��Ă���΍폜
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_elapsedTime > EraseTime) Destroy();

	//������
	m_transform.position += Shot(m_forward);

}

//����
Vector3 Bullet::Shot(Vector3& position) const
{
	//���ʂɔ�΂�
	return position.Normalized() * AddForce * Time::GetInstance()->GetDeltaTime();
}

void Bullet::OnCollision(const ModelActor* other)
{
	//�����蔻��p�̃I�u�W�F�N�g�ɏՓ˂����玩�g���폜
	if (other->GetName() == "HitBox")
	{
		Destroy();
	}
}