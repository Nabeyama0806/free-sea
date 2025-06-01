#pragma once
#include "Vector3.h"
#include "DxLib.h"

class ColliderResult
{
public:
    int m_hitFlag;          //どれかのポリゴンに当たったかどうか
    int m_frameIndex;       //当たったポリゴンが含まれるフレームの番号
    Vector3 HitPosition;    //球とポリゴンの最近点の座標
    Vector3 Position[3];    //当たったポリゴンを形成する三点の座標
    Vector3 Normal;         //当たったポリゴンの法線
    
    //MV1_COLL_RESULT_POLY_DIMからの変換コンストラクタ
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

    //代入演算子によるMV1_COLL_RESULT_POLY_DIMからの変換
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