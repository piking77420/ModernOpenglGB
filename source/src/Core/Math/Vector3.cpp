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
	return std::sqrt(Vector3::DotProduct(*this,*this));
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

	result = (NoramizeNormal * (2.f * (DotProduct(Vector, Normal)))) - Vector;

	return result;
}

Vector3 Vector3::MakePositivEuleur() const
{
	Vector3 euler = *this;
	euler.x = euler.x * Math::Deg2Rad;
	euler.y = euler.y * Math::Deg2Rad;
	euler.z = euler.z * Math::Deg2Rad;


	float value = 180.f;
	float num = -0.005729578f;
	float num2 = value + num;


	if (euler.x < num)
	{
		euler.x += value;
	}
	else if (euler.x > num2)
	{
		euler.x -= value;
	}

	if (euler.y < num)
	{
		euler.y += value;
	}
	else if (euler.y > num2)
	{
		euler.y -= value;
	}

	if (euler.z < num)
	{
		euler.z += value;
	}
	else if (euler.z > num2)
	{
		euler.z -= value;
	}

	euler.x = euler.x * Math::Deg2Rad;
	euler.y = euler.y * Math::Deg2Rad;
	euler.z = euler.z * Math::Deg2Rad;


	return euler;
}












std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << '\n';

	return stream;
}
