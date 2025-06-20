#include "ModelLoader.h"
#include "DxLib.h"

//���\�[�X�̓ǂݍ���
int ModelLoader::Load(const char* path)
{
	LoadData* loadData = nullptr;

	//���ɓǂݍ���ł��邩���`�F�b�N
	auto data = m_dataList.find(path);
	if (data != m_dataList.end())
	{
		//�ǂݍ��ݍς݂̃f�[�^�ŏ���������
		loadData = &data->second;
	}
	else
	{
		//�V�K���[�h
		int id = LoadResource(path);

		//�o�^
		auto result = m_dataList.emplace(path, LoadData(id));

		//�o�^�����f�[�^�ŏ�������
		loadData = &result.first->second;
	}

	//�ǂݍ��݃J�E���g�𑝂₷
	loadData->count++;

	return loadData->id;
}

//���\�[�X�̔j��
void ModelLoader::Delete(int id)
{
	LoadData* loadData = nullptr;

	//���f���n���h���̃t�@�C���p�X���擾
	auto data = m_modelDataList.find(id);

	//�ǂݍ���ł��Ȃ������̂ŉ������Ȃ�
	if (data == m_modelDataList.end()) return;

	//�ǂݍ��݃J�E���g�����炷
	

	//�ǂݍ��݃J�E���g��0�ɂȂ�����j������
	if (loadData->count <= 0)
	{
		//�j��
		DeleteResource(loadData->id);

		//�ꗗ������폜
		//m_dataList.erase();
	}
}

int ModelLoader::LoadResource(const char* path)
{
	return MV1DuplicateModel(MV1LoadModel(path));
}

void ModelLoader::DeleteResource(int id)
{
	MV1DeleteModel(id);
}