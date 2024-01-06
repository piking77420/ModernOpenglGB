#include "Vector4.h"
#include "Vector3.h"
#include "Vector.h"
#include "Vector2.h"
#include "Mathf.h"

float Vector4::Norm() const
{
	float result = x * x + y * y + z * z+ w * w;

	return (float)Math::FSqrtf(result);
}

Vector4 Vector4::Normalize() const
{
	//BIG
	float iNorm = 1.f / Norm();

	Vector4 result = *this;

	result.x *= iNorm;
	result.y *= iNorm;
	result.z *= iNorm;
	result.w *= iNorm;



	return result;
}

Vector4::operator Vector() const
{
	Vector result = Vector(4);

	const float* data = &x;

	for (int i = 0; i < 4; i++)
	{
		result[i] = data[i];
	}

	return result;
}

Vector4::operator Vector2() const
{
	return Vector2(x, y);
}

std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << '\n';

	return stream;
}