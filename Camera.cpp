#include "Camera.h"
#include "Input.h"
#include "Math.h"
#include "Screen.h"
#include <EffekseerForDXLib.h>

//�X�V
void Camera::Update()
{
	// �J�����̎��_�ړ�
	//if(!Input::GetInstance()->IsKeyPress(KEY_INPUT_0))MouseCamera();

	//// �}�E�X�z�C�[����]�ʂ������ɉ�����
	//m_cameraDistance -= Input::GetInstance()->GetMouseHweelRot() * CameraScaling;
	//if (Input::GetInstance()->IsPadPress(PAD_INPUT_6)) m_cameraDistance -= CameraScaling;
	//if (Input::GetInstance()->IsPadPress(PAD_INPUT_5)) m_cameraDistance += CameraScaling;
	//m_cameraDistance > MaxCameraDistance ? m_cameraDistance = MaxCameraDistance : m_cameraDistance < MinCameraDistance ? m_cameraDistance = MinCameraDistance : m_cameraDistance;

	Vector3 tempPosition1;
	Vector3 tempPosition2;
	m_targetPos = m_lookAt->GetPosition();		//�����_��ݒ�
	m_targetPos.y += LookAtHeight;				//�����_�̃I�t�Z�b�g

	//�ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
	float sinParam = static_cast<float>(sin(Math::DegToRad(m_cameraVAngle)));
	float cosParam = static_cast<float>(cos(Math::DegToRad(m_cameraVAngle)));
	tempPosition1.x = 0.0f;
	tempPosition1.y = sinParam * m_cameraDistance;
	tempPosition1.z = -cosParam * m_cameraDistance;

	//���ɐ����p�x�𔽉f�����ʒu���Z�o
	sinParam = static_cast<float>(sin(Math::DegToRad(m_cameraHAngle)));
	cosParam = static_cast<float>(cos(Math::DegToRad(m_cameraHAngle)));
	tempPosition2.x = cosParam * tempPosition1.x - sinParam * tempPosition1.z;
	tempPosition2.y = tempPosition1.y;
	tempPosition2.z = sinParam * tempPosition1.x + cosParam * tempPosition1.z;

	//�Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
	m_cameraPos = tempPosition2 + m_targetPos;
}

//�`��
void Camera::Draw()
{
	// �J�������W�̐ݒ�
	SetCameraNearFar(CameraNear, CameraFar);
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos);
	Effekseer_Sync3DSetting();
}

void Camera::MouseCamera()
{
	//�}�E�X�ŃJ�����̑���
	Input::GetInstance()->SetMouseDispFlag(false);

	// �p�b�h�̉E�X�e�B�b�N�Ń}�E�X�J�[�\���𓮂���
	int padPointX = 0;
	int padPointY = 0;
	DxLib::GetJoypadAnalogInputRight(&padPointX, &padPointY, DX_INPUT_PAD1);

	// ���x����
	Vector2 movePadPoint = Vector2(padPointX, padPointY);
	Input::GetInstance()->SetPadStick(movePadPoint);
	Vector2 mousePos = Input::GetInstance()->GetMousePoint();
	m_cameraHAngle -= (mousePos.x - Screen::Center.x) * CameraAngleSpeed;
	m_cameraVAngle += (mousePos.y - Screen::Center.y) * CameraAngleSpeed;
	Input::GetInstance()->SetMousePoint(static_cast<int>(Screen::Center.x), static_cast<int>(Screen::Center.y));
	if (m_cameraVAngle >= CameraMaxVAngle) m_cameraVAngle = CameraMaxVAngle;
	if (m_cameraVAngle <= CameraMinVAngle) m_cameraVAngle = CameraMinVAngle;
}