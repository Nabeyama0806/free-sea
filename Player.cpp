#include "Player.h"
#include "ModelActor.h"

//�R���X�g���N�^
Player::Player(Camera* camera, Stage* stage, const Vector3& position, PlayerBase::Bullet bullet, int playerIndex) :
	PlayerBase(camera, stage, position, bullet, playerIndex, BulletAmount, ShotCoolTime, BulletFiringRate)
{
}

//�Փ˃C�x���g
void Player::OnCollision(const ModelActor* other)
{
	if (other->GetName() == "Bullet")
	{
		Destroy();
	}
}