#pragma once
#include "Vector3.h"
#include "DxLib.h"

class ColliderResult
{
public:
    int m_hitFlag;          //�ǂꂩ�̃|���S���ɓ����������ǂ���
    int m_frameIndex;       //���������|���S�����܂܂��t���[���̔ԍ�
    Vector3 HitPosition;    //���ƃ|���S���̍ŋߓ_�̍��W
    Vector3 Position[3];    //���������|���S�����`������O�_�̍��W
    Vector3 Normal;         //���������|���S���̖@��
    
    //MV1_COLL_RESULT_POLY_DIM����̕ϊ��R���X�g���N�^
    ColliderResult(const MV1_COLL_RESULT_POLY_DIM& src) :
        m_hitFlag(0),
        m_frameIndex(0)
    {
        if (src.HitNum > 0 && src.Dim != nullptr)
        {
            const MV1_COLL_RESULT_POLY& poly = src.Dim[0];

            m_hitFlag = poly.HitFlag;
            m_frameIndex = poly.FrameIndex;
            HitPosition = Vector3(poly.HitPosition.x, poly.HitPosition.y, poly.HitPosition.z);

            for (int i = 0; i < 3; ++i)
            {
                Position[i] = Vector3(poly.Position[i].x, poly.Position[i].y, poly.Position[i].z);
            }

            Normal = Vector3(poly.Normal.x, poly.Normal.y, poly.Normal.z);
        }
    }

    //������Z�q�ɂ��MV1_COLL_RESULT_POLY_DIM����̕ϊ�
    ColliderResult& operator=(const MV1_COLL_RESULT_POLY_DIM& src)
    {
        if (src.HitNum > 0 && src.Dim != nullptr)
        {
            const MV1_COLL_RESULT_POLY& poly = src.Dim[0];

            m_hitFlag = poly.HitFlag;
            m_frameIndex = poly.FrameIndex;
            HitPosition = Vector3(poly.HitPosition.x, poly.HitPosition.y, poly.HitPosition.z);

            for (int i = 0; i < 3; ++i)
            {
                Position[i] = Vector3(poly.Position[i].x, poly.Position[i].y, poly.Position[i].z);
            }

            Normal = Vector3(poly.Normal.x, poly.Normal.y, poly.Normal.z);
        }
        else
        {
            m_hitFlag = 0;
            m_frameIndex = -1;
        }
        return *this;
    }
};