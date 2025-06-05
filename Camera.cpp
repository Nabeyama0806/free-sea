#include "Camera.h"
#include <EffekseerForDXLib.h>

//•`‰æ
void Camera::Draw()
{
	// ƒJƒƒ‰À•W‚Ìİ’è
	SetCameraNearFar(CameraNear, CameraFar);
	SetCameraPositionAndTarget_UpVecY(CameraPos, m_targetPos);
	Effekseer_Sync3DSetting();
}