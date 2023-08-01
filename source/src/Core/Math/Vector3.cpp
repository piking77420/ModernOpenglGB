#include "Vector3.h"
#include "Vector.h"
#include "Vector4.h"
#include "Mathf.h"





Vector3::operator Vector() const
{
	return Vector(x, y, z);
}

Vector3::operator Vector4() const
{
	return Vector4(x, y, z, 0);
}


Vector3::operator Vector2() const
{
	return Vector2(x, y);
}




inline float Vector3::Norm() const
{
	return std::sqrtf((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::Normalize() const
{
	float norm = Norm();

	if (norm == 1.f)
		return *this;

	return Vector3(x / norm, y / norm, z / norm);	
}


Vector3 Vector3::Reflect(const Vector3& Vector, const Vector3& Normal)
{
	Vector3 result;
	Vector3 NoramizeNormal = Normal.Normalize();

	result = Vector - (NoramizeNormal * (2.f * (DotProduct(Vector, Normal))));

	return result;
}












std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << '\n';

	return stream;
}
