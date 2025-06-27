#include "ModelAnimation.h"
#include "ModelLoader.h"
#include "Transform.h"
#include "Lerp.h"
#include "Time.h"

//�R���X�g���N�^
ModelAnimation::ModelAnimation(const char* animeFileName, const bool isFarst) :
    m_animeFileName(animeFileName),
    m_modelHandle(0),
    m_attachIndex(0),
    m_animeHandle(0),
    m_animeTime(0),
    m_animeTotalTime(0),
    m_blendStart(0),
    m_blendEnd(0),
    m_blendTime(-1),
    m_isFarst(isFarst)
{ 
}

ModelAnimation::~ModelAnimation()
{
    Release();
}

//���\�[�X�̓ǂݍ���
void ModelAnimation::Load(const int modelHandle)
{
    //���f���̎��ʔԍ����擾
    m_modelHandle = modelHandle;

    //�A�j���[�V�����̎��ʔԍ����擾
     m_animeHandle = ModelLoader::GetInstance()->Load(m_animeFileName);

    //�A�^�b�`����A�j���[�V�����̗v�f�ԍ����w��
    //�������A�A�j���[�V�����͌ʂŊǗ����Ă��邽�߁A���0�Ԗڂ��A�^�b�`����
    m_attachIndex = MV1AttachAnim(m_modelHandle, 0, m_animeHandle);

    //�A�j���[�V�����̑��Đ����Ԃ̎擾
    m_animeTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);

    //���݂̃A�j���[�V�����e���x��0�ɂ���
    MV1SetAttachAnimBlendRate(m_modelHandle, m_attachIndex, m_isFarst ? 1.0f : 0.0f);
}

//���\�[�X�̉��
void ModelAnimation::Release()
{
    //�A�j���[�V�����̍폜
    ModelLoader::GetInstance()->Delete(m_animeFileName);
}

//�X�V
void ModelAnimation::Update()
{
    //�Đ����Ԃ����A�j�����Ԃ𒴂���ƍĐ����Ԃ�0�ɂ��ăA�j���[�V���������[�v������
    m_animeTime += Time::GetInstance()->GetDeltaTime();
    if (m_animeTime >= m_animeTotalTime / FPS) m_animeTime = 0;
    MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_animeTime * FPS);

    //�A�j���[�V�����̐؂�ւ�
    if (m_blendTime >= 0)
    {
        //�؂�ւ��ɕK�v�Ȏ��Ԃ����Z���A�������Z�o
        m_blendTime += Time::GetInstance()->GetDeltaTime();
        float t = m_blendTime / BlendDuration;

        //������1�𒴂���ƃA�j���̐؂�ւ�������
        if (t >= 1.0f)
        {
            //�l�����Z�b�g����
            t = 1.0f;
            m_blendTime = -1;
        }

        //�A�j���[�V�����̐؂�ւ�����
        float blendRate = Lerp::Exec(m_blendStart, m_blendEnd, t);
        MV1SetAttachAnimBlendRate(m_modelHandle, m_attachIndex, blendRate);
    }
}
