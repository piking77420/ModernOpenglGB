#include "Vector2.h"
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector.h"


#define Vector2Size 2 




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

Vector2 Vector2::Normalize() const
{
	

	float magnitude = Norm();

	if (magnitude == 1 )
		return *this;

	return Vector2( float(x / magnitude), float(y / magnitude));

}

float Vector2::DotProduct(const Vector2& Row0) const
{
	return x * Row0.x + y * Row0.y ;
}

float Vector2::DotProduct(const Vector2& vec1 , const Vector2& Row1) const
{
	return vec1.x * Row1.x + vec1.y * Row1.y;

}

float Vector2::Norm() const
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

Vector2 Vector2::Normal() const
{
	return Vector2(y, -x).Normalize();
}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{

}

float Vector2::CrossProduct(const Vector2& Row0) const
{
	return Determinant(Row0);
}

float Vector2::Determinant(const Vector2& Row0) const
{
	return (x * Row0.y) - (y * Row0.x);
}

float Vector2::Angle() const
{
	return atan2f(x, y);
}

float Vector2::Angle(const Vector2& vec1 , const Vector2& Row1) const
{
	float dot = DotProduct(vec1, Row1);

	float angle = acosf(dot / (vec1.Norm() * Row1.Norm()));

	if(Determinant(vec1 , Row1) < 0.f )
	{
		return -angle;
	}
	
	return angle;
}


float Vector2::Determinant(const Vector2& vec1 , const Vector2& Row1) const
{
	return vec1.Determinant(Row1);
}


Vector2 Vector2::Rotate(const Vector2 center, const float cos, const float sin) const
{
	Vector2 temp = *this - center;
	return Vector2(temp.x * cos - temp.y * sin, temp.y * cos + temp.x * sin) + center;
}



Vector2 Vector2::Rotation(const float cos, const float sin) const
{
	return Vector2(x * cos -  y * sin , y * cos + x * sin);
}


Vector2 Vector2::Rotate(const float angle, const Vector2 center) const
{
	return Rotate(center, cos(angle), sin(angle));
}


Vector2::Vector2() : x(0) , y(0)
{
	
}

Vector2::~Vector2()
{
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << vec.x << " " << vec.y << " " << '\n';

	return stream;
}
