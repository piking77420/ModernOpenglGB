#include "Vector2.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector.h"
#include "Mathf.h"




const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1, 1);
const Vector2 Vector2::Right = Vector2(1, 0);
const Vector2 Vector2::Left = Vector2(-1, 0);
const Vector2 Vector2::Up = Vector2(0, 1);
const Vector2 Vector2::Down = Vector2(0, -1);








Vector2::operator Vector() const
{
	Vector Row0 = Vector(2);

	Row0[0] = x;
	Row0[1] = y;

	return Row0;
}

Vector2::operator Vector3() const
{
	Vector3 result = Vector3(x, y, 0);

	return result;
}

Vector2::operator Vector4() const
{
	return Vector4(x, y, 0, 0);
}

float Vector2::operator[](int i) const
{
	assert(i >= 0 && i < 2);
	[[assume(i >= 0 && i < 2)]]

	if (i == 0)
		return x;

	if (i == 1)
		return y;
}

float& Vector2::operator[](int i)
{
	assert(i >= 0 && i < 2 );
	[[assume(i >= 0 && i < 2)]]

	if (i == 0)
		return x;
	if (i == 1)
		return y;
}



float* Vector2::SetPtr()
{
	return &x;
}

const float* Vector2::GetPtr() const
{
	return &x;
}

constexpr inline float Vector2::Norm() const
{
	return Math::FSqrtf(x * x + y * y );
}

Vector2 Vector2::Normal() const
{
	return Vector2(y, -x).Normalize();
}

float Vector2::CrossProduct(const Vector2& vec1, const Vector2& vec2) const
{
	return Determinant(vec1,vec2);
}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{

}





float Vector2::Angle() const
{
	return atan2f(x, y);
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
	return std::sqrtf((a.x - b.x * a.x - b.x) + (a.y - b.y * a.y - b.y));
}

float Vector2::Angle(const Vector2& vec1 , const Vector2& Row1) 
{
	float dot = DotProduct(vec1, Row1);

	float angle = std::acosf(dot / (vec1.Norm() * Row1.Norm()));

	if(Determinant(vec1 , Row1) < 0.f )
	{
		return -angle;
	}
	
	return angle;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << vec.x << " " << vec.y << " " << '\n';

	return stream;
}
