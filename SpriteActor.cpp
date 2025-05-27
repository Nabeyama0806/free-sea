#include "SpriteActor.h"
#include "Sprite.h"

//�R���X�g���N�^
SpriteActor::SpriteActor(const char* name, const char* textureName, const Vector3& position) :
	ActorBase(name, textureName, position),
	m_sprite(nullptr)
{
	m_name = name;
	m_transform.position = position;

	//�摜���ݒ肳��Ă���΃X�v���C�g���N��
	if (textureName)
	{
		m_sprite = new Sprite();
		m_sprite->Register(textureName);
	}
}

//���\�[�X�̓ǂݍ���
void SpriteActor::Load()
{
	if (m_sprite)
	{
		m_sprite->Load();
	}

}

//���\�[�X�̉��
void SpriteActor::Release()
{
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
}

//�`��
void SpriteActor::Draw()
{
	if (m_sprite)
	{
		m_sprite->Draw(m_transform);
	}
}

//�q�m�[�h���܂ލX�V
void SpriteActor::TreeUpdate()
{
	//Node�{����TreeUpdate
	Node::TreeUpdate();

	//�X�v���C�g�̍X�V
	if (m_sprite)
	{
		m_sprite->Update();
	}
}