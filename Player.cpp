#include "Player.h"
#include "ModelActor.h"

//コンストラクタ
Player::Player(Camera* camera, Stage* stage, const Vector3& position, PlayerBase::Bullet bullet, int playerIndex) :
	PlayerBase(camera, stage, position, bullet, playerIndex, BulletAmount, ShotCoolTime, BulletFiringRate)
{
}

//衝突イベント
void Player::OnCollision(const ModelActor* other)
{
	if (other->GetName() == "Bullet")
	{
		Destroy();
	}
}