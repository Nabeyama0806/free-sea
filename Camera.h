#pragma once
#include "Vector3.h"
#include "ModelActor.h"

class Camera : public Node
{
private:
	static constexpr Vector3 CameraPos = Vector3(0, 1400, -250);
	static constexpr float CameraNear = 5.0f;
	static constexpr float CameraFar = 1000000.0f;

	ModelActor* m_lookAt;		//注視するオブジェクト
	Vector3 m_targetPos;

protected:
	virtual void Draw();	//描画

public:
	//コンストラクタ
	Camera() :
		m_lookAt(nullptr)
	{
	}

	//注視点の取得
	void SetLookAt(ModelActor* actor)
	{
		m_lookAt = actor;
		m_targetPos = actor->GetPosition() + Vector3(0, -200, 0);
	}

	Vector3 GetForward() const
	{
		return (m_targetPos - CameraPos).Normalized();
	}

	Vector3 GetRight() const
	{
		return Vector3::Cross(Vector3(0, 1, 0), GetForward()).Normalized();
	}

	Vector3 GetCameraPos() const
	{
		return CameraPos;
	}
};