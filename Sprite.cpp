#include "Sprite.h"
#include "Time.h"
#include "SpriteLoader.h"
#include "DxLib.h"

//�f�X�g���N�^
Sprite::~Sprite()
{
	Release();
}

// ���\�[�X�̓ǂݍ���
void Sprite::Load()
{
	int firstTexture = 0;
	for (auto& pair : m_spriteAnimationList)
	{
		//���X�g����<�A�j���[�V�������F�f�[�^>�̃y�A�����o��
		//pair.first : �A�j���[�V������
		//pair.secon�F�f�[�^

		//�f�[�^����摜�p�X��ǂݍ���Ō��߂�
		pair.second.textureId = SpriteLoader::GetInstance()->Load(pair.second.textureName);

		if (!firstTexture)
		{
			firstTexture = pair.second.textureId;
		}
	}

	//�O���b�h�T�C�Y���w�肵�Ȃ������ꍇ�́A�摜����T�C�Y���擾
	if (gridSize.IsZero())
	{
		int w, h;
		GetGraphSize(firstTexture, &w, &h);
		gridSize = Vector2(w, h);
	}
}
//���\�[�X�̊J��
void Sprite::Release()
{
	for (auto& pair : m_spriteAnimationList)
	{
		SpriteLoader::GetInstance()->Delete(pair.second.textureName);
	}

	m_spriteAnimationList.clear();
	m_runningAnime = nullptr;
}
//�X�V
void Sprite::Update()
{
	//�A�j���[�V�������I�����Ă��Ȃ���
	if (IsFinishAnime()) return;

	//�o�ߎ��Ԃ̉��Z
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();

	//�o�ߎ��Ԃ������A�j���[�V�������Ԃ𒴂����烋�[�v����
	if (IsFinishAnime() && m_runningAnime->loopFlag)
	{
		//�ŏ��̃R�}�ɖ߂�
		m_elapsedTime = 0;
	}
}

//�`��
void Sprite::Draw(const Transform& transform)
{
	//�Đ�������̂��Ȃ���Ή������Ȃ�
	if (!m_runningAnime) return;
	//�`�悷��R�}���v�Z
	int gridIndex;
	if (IsFinishAnime())
	{
		gridIndex = m_runningAnime->gridAmount - 1;
	}
	else
	{
		//�o�ߎ���
		gridIndex = static_cast<int> (m_elapsedTime / GetFrameTime());
	}
	//�`��
	DrawRectRotaGraph(
		static_cast<int>(transform.position.x), static_cast<int>(transform.position.y),
		static_cast<int>(gridSize.x) * gridIndex, 0,
		static_cast<int>(gridSize.x), static_cast<int>(gridSize.y),
		transform.scale.x,
		transform.rotation.x,
		m_runningAnime->textureId,
		true,
		flipX, flipY
	);

#ifdef _DEBUG

	//�O���b�h�g�̕\��
	/*DrawBox(
		static_cast<int>(transform.position.x - gridSize.x * transform.scale / 2),
		static_cast<int>(transform.position.y - gridSize.y * transform.scale / 2),
		static_cast<int>(transform.position.x + gridSize.x * transform.scale / 2),
		static_cast<int>(transform.position.y + gridSize.y * transform.scale / 2),
		GetColor(255, 0, 0), false
	);*/
#endif // _DEBUG2
}

//�A�j���[�V�����o�^

void Sprite::Register(const char* textureName)
{
	Register("-", SpriteAnimation(textureName, 1, 1, false));

}

void Sprite::Register(const char* animeName, const SpriteAnimation& spriteAnimetion)
{
	m_spriteAnimationList.emplace(animeName, spriteAnimetion);

	//�ŏ��ɓo�^���ꂽ�A�j���[�V�������Đ����A�j���[�V�����Ƃ���
	if (!m_runningAnime)
	{
		m_runningAnime = &m_spriteAnimationList.begin()->second;
	}
}

//�A�j���[�V�����Đ�
void Sprite::Play(const char* animeName)
{
	//�w�肳�ꂽ�A�j���[�V���������X�g����擾
	const auto& pair = m_spriteAnimationList.find(animeName);

	//���o�^�̃A�j���[�V������
	if (pair == m_spriteAnimationList.end()) return;

	//���ݍĐ����̃A�j���[�V�����Ɠ���
	if (m_runningAnime == &pair->second) return;

	//�A�j���[�V�����̐؂�ւ�
	m_runningAnime = &pair->second;
	m_elapsedTime = 0;
}
