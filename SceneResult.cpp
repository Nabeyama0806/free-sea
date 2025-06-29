#include "SceneResult.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "SpriteAnimation.h"
#include "Screen.h"
#include "Time.h"

//������
void SceneResult::Initialize()
{
	m_rootNode = new Node();

	//�w�i
	m_rootNode->AddChild(new SpriteActor("Result", "Resource/Texture/result.png", Screen::Center));

	//���ʉ��̍Đ�
	SoundManager::Play("Resource/Sound/se_winner.mp3");

	//�p�����
	m_transform.position = Screen::Center;

	//�摜�̓ǂݍ���
	m_sprite = new Sprite();
	m_sprite->Register(TextureName[m_playerIndex], SpriteAnimation(TextureFilePath[m_playerIndex]));
	m_sprite->Load();
	m_sprite->Play(TextureName[m_playerIndex]);
}

//�I������
void SceneResult::Finalize()
{
	m_rootNode->TreeRelease();
	delete m_rootNode;
	m_rootNode = nullptr;
}

//�X�V
void SceneResult::Update()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeUpdate();

	//�摜�̍X�V
	m_sprite->Update();

	if (m_waitTransitionTime > 0)
	{
		m_waitTransitionTime -= Time::GetInstance()->GetDeltaTime();
	}

	//�����ꂩ�̃L�[�������ꂽ��^�C�g����ʂɑJ��
	if (m_waitTransitionTime <= 0 && InputSystem::GetInstance()->IsAnyKeyDown())
	{
		SceneManager::GetInstance()->LoadScene(new SceneTitle());
	}
}

//�`��
void SceneResult::Draw()
{
	//�m�[�h�̍X�V
	m_rootNode->TreeDraw();

	//�摜�̕\��
	m_sprite->Draw(m_transform);
}