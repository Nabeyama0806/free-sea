#pragma once

class Time
{
private:
	int m_oldTime;		// ���O�̒[���o�ߎ���
	float m_deltaTime;	// �O����s����Update�֐�����̌o�ߎ���

	Time();

public:
	// �V���O���g��
	static Time* GetInstance()
	{
		static Time instance;
		return &instance;
	}

	void Update();
	float GetDeltaTime(){ return m_deltaTime; }
};
