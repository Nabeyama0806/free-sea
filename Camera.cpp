#include "Camera.h"
#include <EffekseerForDXLib.h>

//�`��
void Camera::Draw()
{
	// �J�������W�̐ݒ�
	SetCameraNearFar(CameraNear, CameraFar);
	SetCameraPositionAndTarget_UpVecY(CameraPos, m_targetPos);
	Effekseer_Sync3DSetting();
}