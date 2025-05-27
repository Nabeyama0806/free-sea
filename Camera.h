#pragma once
#include "Node.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Transform.h"
#include "ModelActor.h"

class Instructions;

class Camera : public Node
{
private:
	static constexpr Vector3 SpawnPos = Vector3(0, 170, -400);
	static constexpr float CameraAngleSpeed = 0.1f;	//�J�����̉�]���x
	static constexpr float CameraScaling = 60;		//�J�����̊g�嗦
	static constexpr float CameraNear = 5.0f;
	static constexpr float CameraFar = 1000000.0f;
	static constexpr float MaxCameraDistance = 800;
	static constexpr float MinCameraDistance = 200;
	static constexpr float LookAtHeight = 200;			//�����_����̍����̃I�t�Z�b�g
	static constexpr float CameraMaxVAngle = 80.0f;		//�J�����̏c��]�̍ő�l
	static constexpr float CameraMinVAngle = -80.0f;	//�J�����̏c��]�̍ŏ��l

	Transform* m_transform;		//�p�����
	ModelActor* m_lookAt;		//��������I�u�W�F�N�g
	Vector3 m_targetPos;		//�����_���W
	Vector3 m_cameraPos;		//�J�������W
	Vector3 m_cameraAngle;		//�J�����p�x

	float m_cameraDistance;	//�J�������W�܂ł̋���
	float m_cameraHAngle;		//����]
	float m_cameraVAngle;		//�c��]

	bool m_isDisplayMouse;		//�}�E�X�J�[�\���̕\��

	void MouseCamera();

protected:
	virtual void Update();	//�X�V
	virtual void Draw();	//�`��

public:
	//�R���X�g���N�^
	Camera() :
		m_transform(nullptr),
		m_lookAt(nullptr),
		m_cameraDistance(400),
		m_cameraHAngle(0),
		m_cameraVAngle(0),
		m_isDisplayMouse(false)
	{
		m_transform = new Transform();
	}

	//�����_�̎擾
	void SetLookAt(ModelActor* actor)
	{
		m_lookAt = actor;
	}

	float GetHAngle()
	{
		return m_cameraHAngle;
	}

	float GetVAngle()
	{
		return m_cameraVAngle;
	}

	Vector3 GetForward() const
	{
		return (m_targetPos - m_cameraPos).Normalized();
	}

	Vector3 GetRight() const
	{
		return Vector3::Cross(Vector3(0, 1, 0), GetForward()).Normalized();
	}

	Vector3 GetCameraPos() const
	{
		return m_cameraPos;
	}
};