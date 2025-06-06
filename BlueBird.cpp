#include "BlueBird.h"
#include "StraightBullet.h"
#include "ReflectionBullet.h"
#include "Time.h"
#include "InputSystem.h"
#include "SoundManager.h"

//�R���X�g���N�^
BlueBird::BlueBird(Camera* camera, Stage* stage, const Vector3& position, int playerIndex) :
	CharacterBase("Man/Man.mv1", camera, stage, position, Health, playerIndex)
{
	//�e
	m_maxBulletAmount = BulletAmount;
	m_shotCoolTime = ShotCoolTime;
	m_bulletFiringRate = BulletFiringRate;
}

void BlueBird::Update()
{
	//�{���̍X�V
	CharacterBase::Update();

	//�e�̔���
	BulletShot();
}

//�e�̔���
void BlueBird::BulletShot()
{
	//���ɔ��ˍς�
	if (m_isShot)
	{
		//�e�̔��ˊԊu�̌o�ߎ���
		m_bulletElapsedTime += Time::GetInstance()->GetDeltaTime();

		//���������e�̐������Z
		if (BulletInstance()) m_bulletInstanceAmount++;

		//�ő吔�܂Ő���������t���O��܂�
		if (m_bulletInstanceAmount == m_maxBulletAmount)
		{
			m_isShot = false;
			m_bulletInstanceAmount = 0;
		}
	}

	//���˂̓��͎�t�̌o�ߎ���
	m_shotElapsedTime += Time::GetInstance()->GetDeltaTime();
	if (m_shotElapsedTime < m_shotCoolTime) return;

	//���˃{�^���������ꂽ��e�𐶐�
	if (InputSystem::GetInstance()->IsDecision(static_cast<InputSystem::ActionMap>(m_playerIndex)))
	{
		m_isShot = true;
		m_shotElapsedTime = 0;
	}
}

//�e�̐���
bool BlueBird::BulletInstance()
{
	//�e�Ԃ̌o�ߎ��Ԃ����˃��[�g�𒴂��Ă���Βe�𔭎�
	if (m_bulletElapsedTime > m_bulletFiringRate)
	{
		//�o�ߎ��Ԃ̃��Z�b�g
		m_bulletElapsedTime = 0;

		//���ʂ���e�𔭎˂���
		Vector3 forward = (m_transform.rotation * Vector3(0, 0, -1)).Normalized();
		Vector3 instancePos = m_transform.position + BulletOffset + forward * 60;
		AddChild(new ReflectionBullet(instancePos, forward, m_stage));

		//���ʉ��̍Đ�
		SoundManager::Play("Resource/Sound/se_bubble_shot.mp3");

		return true;
	}
	return false;
}