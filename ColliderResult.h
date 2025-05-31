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
    
    //当たり判定の結果を取得
    ColliderResult* GetColliderResult(const MV1_COLL_RESULT_POLY_DIM& src)
    {
        if (src.HitNum > 0 && src.Dim)
        {
            //当たり判定の結果が格納されている構造体を取得
            const MV1_COLL_RESULT_POLY& poly = src.Dim[0];

            //当たり判定の結果を各メンバ変数に代入
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
        }

        return this;
    }
};