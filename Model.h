#pragma once
#include <vector>

class ModelAnimation;
class Transform;

class Model
{
public:
	enum class Anime
	{
		Idle,
		Run,

		Length,
	};

private:
	std::vector<ModelAnimation*> m_animeList;	//�A�j���[�V�����z��
	ModelAnimation* m_prevAnime;					//�ȑO�̃A�j��
	ModelAnimation* m_nowAnime;					//���݂̃A�j��
	float m_elapsedTime;					//�o�ߎ���(�b)
	int m_modelHandle;						//���f����ID
	const char* m_modelFileName;			//���f���̃t�@�C���p�X

public:
	//�R���X�g���N�^
	Model(const char* modelFileName);

	//�f�X�g���N�^
	virtual ~Model();

	//���f���̓ǂݍ���
	void Load();

	//���f���̉��
	void Release();

	//�X�V
	void Update();

	//�`��
	void Draw(const Transform& transform);

	//�A�j���[�V�����̓o�^
	void Register(const char* animeFileName);

	//�A�j���[�V�����̐؂�ւ�
	void PlayAnime(int animeIndex);
};