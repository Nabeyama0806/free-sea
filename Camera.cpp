#include "Camera.h"
#include <EffekseerForDXLib.h>

//描画
void Camera::Draw()
{
	// カメラ座標の設定
	SetCameraNearFar(CameraNear, CameraFar);
	SetCameraPositionAndTarget_UpVecY(CameraPos, m_targetPos);
	Effekseer_Sync3DSetting();
}