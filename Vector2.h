#pragma once

//クラスの前方宣言
class Vector3;

class Vector2
{
public:
	float x;
	float y;

	//コンストラクタ
	constexpr Vector2():
		x(0),
		y(0){}

	template<typename T1, typename T2>
	constexpr Vector2(T1 x, T2 y) :
		x(static_cast<float>(x)),
		y(static_cast<float>(y)){}

	//vector3へのキャスト
	operator Vector3() const;

	//加算
	constexpr Vector2 operator + (const Vector2& other) const	//vector2 + Vector2
	{
		return Vector2(x + other.x, y + other.y);
	}
	constexpr Vector2& operator += (const Vector2& other)		//vector2 += Vector2
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	//減算
	constexpr Vector2 operator - (const Vector2& other) const	//vector2 - Vector2
	{
		return Vector2(x - other.x, y - other.y);
	}
	constexpr Vector2& operator -= (const Vector2& other)		//vector2 -= Vector2
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	//乗算
	constexpr Vector2 operator * (const float& scalar) const //Vector2 * scalar
	{
		return Vector2(x * scalar, y * scalar);
	}
	constexpr friend Vector2 operator * (const float& scalar, const Vector2& v)//scalar * Vector2
	{
		return v * scalar;
	}
	constexpr Vector2& operator *= (const float& scalar)		//vector2 *= scalar
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	//除算
	constexpr Vector2 operator / (const float& scalar) const //Vector2 / scalar
	{
		return Vector2(x / scalar, y / scalar);
	}
	constexpr Vector2& operator /= (const float& scalar)		//vector2 /= scalar
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	//負(単項)
	constexpr Vector2 operator - () const	//-Vector2
	{
		return Vector2(-x, -y);
	}

	//等価
	constexpr bool operator == (const Vector2& other) const	//Vector2 == Vector2
	{
		return (x == other.x) && (y == other.y);
	}

	//非等価
	constexpr bool operator != (const Vector2& other) const	//Vector2 != Vector2
	{
		return !(*this == other);
	}

	//ゼロ判定(不完全)
	constexpr bool IsZero() const
	{
		return (x == 0) && (y == 0);
	}

	//2つのベクトルの内積を取得
	static constexpr float Dot(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	constexpr float Dot(const Vector2& v) const
	{
		return Dot(*this, v);
	}

	//2つのベクトルの外積を取得
	static constexpr float Cross(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
	constexpr float Cross(const Vector2& v)
	{
		return Cross(*this, v);
	}

	//正規化
	static Vector2 Normalize(const Vector2& v)
	{
		Vector2 tmp = v;
		
		float m = tmp.Magnitude();
		tmp.x /= m;
		tmp.y /= m;

		return tmp;
	}
	Vector2& Normalize()
	{
		*this = Normalize(*this);
		return *this;
	}

	//正規化
	Vector2 Normalized() const
	{
		return Normalize(*this);
	}

	//長さの2乗を取得
	constexpr float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	//長さを取得
	float Magnitude() const;
};