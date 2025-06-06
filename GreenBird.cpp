#include "GreenBird.h"
#include "StraightBullet.h"
#include "Time.h"
#include "InputSystem.h"
#include "SoundManager.h"

//コンストラクタ
GreenBird::GreenBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex) :
	CharacterBase("Man/Man2.mv1", camera, stage, position, Health, playerIndex)
{
	//弾
	m_maxBulletAmount = BulletAmount;
	m_shotCoolTime = ShotCoolTime;
	m_bulletFiringRate = BulletFiringRate;
}

void GreenBird::Update()
{
	//本来の更新
	CharacterBase::Update();

	//弾の発射
	BulletShot();
}

//弾の発射
void GreenBird::BulletShot()
{
	//既に発射済み
	if (m_isShot)
	{
		//弾の発射間隔の経過時間
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//生成した弾の数を加算
		if (BulletInstance()) m_bulletInstanceAmount++;

		//最大数まで生成したらフラグを折る
		if (m_bulletInstanceAmount == m_maxBulletAmount)
		{
			m_isShot = false;
			m_bulletInstanceAmount = 0;
		}
	}

	//発射の入力受付の経過時間
	m_shotElapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_shotElapsedTime < m_shotCoolTime) return;

	//発射ボタンが押されたら弾を生成
	if (InputSystem::GetInstance()->IsDecision(static_cast<InputSystem::ActionMap>(m_playerIndex)))
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//弾の生成
bool GreenBird::BulletInstance()
{
	//弾間の経過時間が発射レートを超えていれば弾を発射
	if (m_bulletElapsedTime > m_bulletFiringRate)
	{
		//経過時間のリセット
		m_bulletElapsedTime = 0;

		//正面から弾を発射する
		Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
		Vector3 instancePos = m_transform.position + BulletOffset + forward * 50;
		AddChild(new StraightBullet(instancePos, forward, m_stage));

		//効果音の再生
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}