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
	return Vector4(x, y, z, 0.f);
}

Vector3::operator Vector2() const
{
	return Vector2(x, y);
}






















std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << '\n';

	return stream;
}
