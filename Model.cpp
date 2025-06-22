#include "Model.h"
#include "ModelAnimation.h"
#include "ModelLoader.h"
#include "Transform.h"
#include "Math.h"
#include "Dxlib.h"

//�f�X�g���N�^
Model::~Model()
{
	Release();
}

//�R���X�g���N�^
Model::Model(const char* modelFileName) :
	m_modelHandle(0),
	m_modelFileName(modelFileName),
	m_prevAnime(nullptr),
	m_nowAnime(nullptr),
	m_elapsedTime(0)
{
}

//���\�[�X�̓ǂݍ���
void Model::Load()
{
	m_modelHandle = ModelLoader::GetInstance()->Load(m_modelFileName);
	for (auto anime : m_animeList)
	{
		anime->Load(m_modelHandle);
	}
}

//���\�[�X�̉��
void Model::Release()
{
	//���f���f�[�^�̍폜
	ModelLoader::GetInstance()->Delete(m_modelHandle);

	//�A�j���[�V�����̍폜
	for (auto anime : m_animeList)
	{
		delete anime;
		anime = nullptr;
	}
}

//�X�V
void Model::Update()
{
	if (m_nowAnime) m_nowAnime->Update();
	if (m_prevAnime)
	{
		m_prevAnime->Update();
		if (!m_prevAnime->IsFade()) m_prevAnime = nullptr;
	}
}

//�`��
void Model::Draw(const Transform& transform)
{
	//���f���̎p������ݒ�	
	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetScale(Vector3(transform.scale, transform.scale, transform.scale)));
	mat = MMult(mat, transform.rotation);
	mat = MMult(mat, MGetTranslate(transform.position));
	MV1SetMatrix(m_modelHandle, mat);

	//���f���̕`��
	MV1DrawModel(m_modelHandle);
}

//�A�j���[�V�����o�^
void Model::Register(const char* animeFileName)
{
	//�A�j���[�V�����̍쐬
	ModelAnimation* anime = new ModelAnimation(animeFileName, m_animeList.empty());

	//���X�g�ɓo�^
	m_animeList.push_back(anime);
	if (!m_nowAnime) m_nowAnime = anime;
}

//�A�j���[�V�����̐؂�ւ�
void Model::PlayAnime(int animeIndex)
{
	//�ύX��̃A�j���ƌ��݂̃A�j���������Ȃ牽�����Ȃ�
	if (m_animeList[animeIndex] == m_nowAnime) return;

	//���݂̃A�j�����ȑO�̃A�j���ɕύX
	m_prevAnime = m_nowAnime;

	//���݂̃A�j���������̃A�j���ɕύX
	m_nowAnime = m_animeList[animeIndex];

	//�A�j���[�V�������t�F�[�h������
	m_nowAnime->FadeIn();
	m_prevAnime->FadeOut();
}
