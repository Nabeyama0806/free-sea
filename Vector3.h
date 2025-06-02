#pragma once
#include "DxLib.h"
#include "Math.h"

//�N���X�̑O���錾
class Vector2;

class Vector3
{
public:
	float x;
	float y;
	float z;

	//�R���X�g���N�^
	constexpr Vector3():
		x(0),
		y(0),
		z(0) {}

	template<typename T1, typename T2, typename T3>
	constexpr Vector3(T1 x, T2 y, T3 z) :
		x(static_cast<float>(x)),
		y(static_cast<float>(y)),
		z(static_cast<float>(z)){}

	//Vector2�ւ̃L���X�g
	operator Vector2() const;

	//VECTOR�ւ̃L���X�g
	operator  VECTOR() const;
	constexpr friend Vector3 operator == (const Vector3& v, const VECTOR& other)
	{
		return Vector3(other.x, other.y, other.z);
	}

	//���Z
	constexpr Vector3 operator + (const Vector3& other) const	//Vector3 + Vector3
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	constexpr Vector3& operator += (const Vector3& other)		//Vector3 += Vector3
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	//���Z
	constexpr Vector3 operator - (const Vector3& other) const	//Vector3 - Vector3
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	constexpr Vector3& operator -= (const Vector3& other)		//Vector3 -= Vector3
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	//��Z
	constexpr Vector3 operator * (const float& scalar) const //Vector3 * scalar
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}
	constexpr friend Vector3 operator * (const float& scalar, const Vector3& v)//scalar * Vector3
	{
		return v * scalar;
	}
	constexpr Vector3& operator *= (const float& scalar)		//Vector3 *= scalar
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	//���Z
	const Vector3 operator / (const float& scalar) const	//Vector3 / scalar
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}
	constexpr Vector3& operator /= (const float& scalar)	//Vector3 /= scalar
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	//��(�P��)
	constexpr Vector3 operator - () const	//-Vector3
	{
		return Vector3(-x, -y, -z);
	}

	//����
	constexpr bool operator == (const Vector3& other) const	//Vector3 == Vector3
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	//�񓙉�
	constexpr bool operator != (const Vector3& other) const	//Vector3 != Vector3
	{
		return !(*this == other);
	}

	//�[������(�s���S)
	static constexpr bool IsZero(const Vector3& v)
	{
		return (v.x == 0) && (v.y == 0) && (v.z == 0);
	}
	constexpr bool IsZero() const
	{
		return IsZero(*this);
	}

	//������2����擾
	static constexpr float SqrMagnitude(const Vector3& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	constexpr float SqrMagnitude() const
	{
		return SqrMagnitude(*this);
	}

	//2�̃x�N�g���̓��ς��擾
	static constexpr float Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	constexpr float Dot(const Vector3& v) const
	{
		return Dot(*this, v);
	}

	//2�̃x�N�g���̊O�ς��擾
	static constexpr Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}
	constexpr Vector3 Cross(const Vector3& v)
	{
		return Cross(*this, v);
	}

	//2�_�Ԃ̊p�x���擾
	static float Angles(Vector3 from, Vector3 to)
	{
		float num = static_cast<float>(std::sqrt(from.SqrMagnitude() * to.SqrMagnitude()));
		if (num < 1E-15f)
		{
			return 0.0f;
		}

		float num2 = Math::Clamp(Dot(from, to) / num, -1.0f, 1.0f);
		return (float)std::acos(num2);
	}

	//�������擾
	static float Magnitude(const Vector3& v)
	{
		return std::sqrtf(SqrMagnitude(v));
	}
	float Magnitude() const
	{
		return Magnitude(*this);
	}

	//�X�P�[���̎擾
	static Vector3 Scale(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}
	Vector3 Scale(const Vector3& v) const
	{
		return Scale(*this, v);
	}

	//���K��
	static Vector3 Normalize(const Vector3& v)
	{
		Vector3 tmp = v;

		float m = Magnitude(tmp);
		tmp.x /= m;
		tmp.y /= m;
		tmp.z /= m;

		return tmp;
	}
	Vector3& Normalize()
	{
		*this = Normalize(*this);
		return *this;
	}

	//���K��
	Vector3 Normalized() const
	{
		return Normalize(*this);
	}
};