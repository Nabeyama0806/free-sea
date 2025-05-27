#include "Time.h"
#include "DxLib.h"

Time::Time()
{
	m_oldTime = GetNowCount();
	m_deltaTime = 0;
}

void Time::Update()
{
	// �[�����N�����Ă���̌o�ߎ��ԁi�P�� �~���b�j���擾
	int nowTime = GetNowCount();

	// �O��Ƃ̍�����P�� �b�œ���
	m_deltaTime = (nowTime - m_oldTime) / 1000.0f;

	// �[���̌o�ߎ��Ԃ̕ێ�
	m_oldTime = nowTime;
}
