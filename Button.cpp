#include "Button.h"
#include "Input.h"
#include "SoundManager.h"

// �R���X�g���N�^
Button::Button(const Vector2& size, int mouseButton, std::function<void()> callbackFunction) :
	m_size(size),
	m_mouseButton(mouseButton),
	m_callbackFunction(callbackFunction),
	m_isClickDown(false)
{
}

//�}�E�X�J�[�\�����{�^���͈͓̔��ɂ��邩�𔻒�
bool Button::IsMouseContain(const Vector2& position)
{
	// ��`(�{�^��)�ɓ_(�}�E�X)���܂܂�Ă��邩
	Vector2 mousePoint = Input::GetInstance()->GetMousePoint();
	if (position.x - m_size.x / 2 <= mousePoint.x && mousePoint.x <= position.x + m_size.x / 2
		&& position.y - m_size.y / 2 <= mousePoint.y && mousePoint.y <= position.y + m_size.y / 2)
	{
		return true;
	}
	return false;
}

//�X�V
void Button::Update(const Vector2& position)
{
	// �{�^����Ŏw�肳�ꂽ�}�E�X�{�^���������ꂽ��
	if (Input::GetInstance()->IsDecision())
	{
		m_isClickDown = IsMouseContain(position);
	}

	// �{�^����Ŏw�肳�ꂽ�}�E�X�{�^������������
	if (m_isClickDown && Input::GetInstance()->IsDecisionUp())
	{
		m_isClickDown = false;
		if (IsMouseContain(position))
		{
			// �R�[���o�b�N�֐��Ăяo��
			m_callbackFunction();

			//���ʉ��̍Đ�
			SoundManager::Play("Resource/sound/se_start.mp3");
		}
	}
}

//�`��
void Button::Draw(const Vector2& position)
{
	//�{�^����Ƀ}�E�X�J�[�\����������Ή������Ȃ�
	if (!IsMouseContain(position)) return;

	//�`��
	DrawBox(
		static_cast<int>(position.x - m_size.x / 2), static_cast<int>(position.y - m_size.y / 2),
		static_cast<int>(position.x + m_size.x / 2), static_cast<int>(position.y + m_size.y / 2),
		GetColor(255, 255, 0), 0);
}
