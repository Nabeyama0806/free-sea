#pragma once
#include "Vector3.h"
#include <cmath>

struct Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	// �R���X�g���N�^
	constexpr Quaternion() :
		x(0),
		y(0),
		z(0),
		w(1) {}
	constexpr Quaternion(float x, float y, float z, float w) :
		x(x),
		y(y),
		z(z),
		w(w) {}

	operator MATRIX() const;		// �s��ւ̕ϊ�

	constexpr Vector3 operator*(const Vector3& v)
	{
		float x2 = x * 2.0f;
		float y2 = y * 2.0f;
		float z2 = z * 2.0f;
		float xx = x * x2;
		float yy = y * y2;
		float zz = z * z2;
		float xy = x * y2;
		float xz = x * z2;
		float yz = y * z2;
		float wx = w * x2;
		float wy = w * y2;
		float wz = w * z2;

		Vector3 res;
		res.x = (1.0f - (yy + zz)) * v.x + (xy - wz) * v.y + (xz + wy) * v.z;
		res.y = (xy + wz) * v.x + (1.0f - (xx + zz)) * v.y + (yz - wx) * v.z;
		res.z = (xz - wy) * v.x + (yz + wx) * v.y + (1.0f - (xx + yy)) * v.z;
		return res;
	}

	// ��Z
	constexpr Quaternion operator*(const Quaternion& other)
	{
		return Quaternion(
			w * other.x + x * other.w + y * other.z + -z * other.y,
			w * other.y + y * other.w + z * other.x + -x * other.z,
			w * other.z + z * other.w + x * other.y + -y * other.x,
			w * other.w + -x * other.x + -y * other.y + -z * other.z
		);
	}
	constexpr Quaternion& operator*=(const Quaternion& other)
	{
		*this = operator*(other);
		return *this;
	}

	Quaternion Conjugate() const;	

	// �����̂Q���Ԃ�
	float LengthSquared() const;	

	// ������Ԃ�
	float Length() const;

	// �l�����𐳋K������
	static Quaternion Normalized(const Quaternion& q)
	{
		float m = q.Length();
		return Quaternion(q.x / m, q.y / m, q.z / m, q.w / m);
	}
	Quaternion Normalized() const
	{
		return Normalized(*this);
	}
	void Normalize()
	{
		*this = Normalized();
	}

	// ���ς����߂�
	static float Dot(const Quaternion &q1, const Quaternion &q2);

	// ���ʐ��`��Ԃ��s��(t��0�`1)
	static Quaternion Slerp(const Quaternion &from, Quaternion to, float t);

	// �l�����̍쐬
	static Quaternion AngleAxis(float rad, Vector3 axis);			//�C�ӎ���]�̎l�����̍쐬
	static Quaternion FromToRotation(const Vector3& from, const Vector3& to);			//������ύX���邽�߂̉�]�̎l�����̍쐬(2�̃x�N�g����180�x�̏ꍇ�͖���`)
	static Quaternion LookRotation(const Vector3& forward);

	// �l�����̐ݒ�
	void SetRotationAxis(float rad, const Vector3& axis);			//�C�ӎ���]�̎l�����̐ݒ�
	void SetRotationDirection(Vector3 from, Vector3 to);		//������ύX���邽�߂̉�]�̎l�����̐ݒ�(2�̃x�N�g����180�x�̏ꍇ�͖���`)
};

// �����l������Ԃ�
inline Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

// �l�����̃X�J���[�{
inline Quaternion operator*(const Quaternion &q, float f)
{
	return Quaternion(q.x * f, q.y * f, q.z * f, q.w * f);
}

// �����̂Q���Ԃ�
inline float Quaternion::LengthSquared() const
{
	return x * x + y * y + z * z + w * w;
}

// ������Ԃ�
inline float Quaternion::Length() const
{
	return sqrt(LengthSquared());
}

// 2�̎l�����̓��ς����߂�
inline float Quaternion::Dot(const Quaternion &q1, const Quaternion &q2)
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}
