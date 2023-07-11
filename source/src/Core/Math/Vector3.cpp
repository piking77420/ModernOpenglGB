#include "Vector3.h"
#include "Vector.h"
#include "Vector4.h"
#include "Mathf.h"

const Vector3 Vector3::Zero = Vector3(0.f, 0.f, 0.f);
const Vector3 Vector3::One = Vector3(1.f, 1.f, 1.f);
const Vector3 Vector3::Right = Vector3(1.f, 0.f, 0.f);
const Vector3 Vector3::Left = Vector3(-1.f, 0.f, 0.f);
const Vector3 Vector3::Up = Vector3(0.f, 1.f, 0.f);
const Vector3 Vector3::Down = Vector3(0.f, -1.f, 0.f);
const Vector3 Vector3::Forward = Vector3(0.f, 0.f, 1.f);
const Vector3 Vector3::BackForward = Vector3(0.f, 0.f, -1.f);




Vector3::operator Vector() const
{
	return Vector(x, y, z);
}

Vector3::operator Vector4() const
{
	return Vector4(x, y, z, 0);
}


float Vector3::operator[](int i) const
{
	assert(i >= 0 && i < 3);

	if (i == 0)
		return x;

	if (i == 1)
		return y;

	if (i == 2)
		return z;

}

float& Vector3::operator[](int i)
{
	assert(i >= 0 && i < 3);

	if (i == 0)
		return x;

	if (i == 1)
		return y;

	if (i == 2)
		return z;
}

Vector3::operator Vector2() const
{
	return Vector2(x, y);
}

Vector3::Vector3(const Vector4& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;

}

Vector3::Vector3(float _x, float  _y, float _z) : x(_x), y(_y), z(_z)
{
}









constexpr inline float Vector3::Norm() const
{
	return Math::FSqrtf((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::Reflect(const Vector3& Vector, const Vector3& Normals)
{
	Vector3 result = Vector3(0, 0, 0);
	Vector3 NoramizeNormal = Normals.Normalize();

	result = Vector - (NoramizeNormal * (2.f * (DotProduct(Vector, Normals))));

	return result;
}












std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << '\n';

	return stream;
}
