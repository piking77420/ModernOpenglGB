#include "Vector2.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector.h"
#include "Mathf.h"












Vector2::operator Vector() const
{
	Vector Row0 = Vector(2);

	Row0[0] = x;
	Row0[1] = y;

	return Row0;
}

Vector2::operator Vector3() const
{
	return  Vector3(x, y, 0);
}

Vector2::operator Vector4() const
{
	return Vector4(x, y, 0, 0);
}








constexpr inline float Vector2::Norm() const
{
	return (float)Math::FSqrtf(x * x + y * y );
}


float Vector2::Angle() const
{
	return std::atan2f(x, y);
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
	return std::sqrtf((a.x - b.x * a.x - b.x) + (a.y - b.y * a.y - b.y));
}

float Vector2::Angle(const Vector2 vec1 , const Vector2 Row1) 
{
	float dot = DotProduct(vec1, Row1);

	float angle = std::acos(dot / (vec1.Norm() * Row1.Norm()));

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
