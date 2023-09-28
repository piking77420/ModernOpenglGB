#include "Vector4.h"
#include "Vector3.h"
#include "Vector.h"
#include "Vector2.h"
#include "Mathf.h"



Vector4 Vector4::operator+(float value)
{
	return Vector4(x + value, y + value, z + value, w + value);

}



Vector4 Vector4::operator-(float value)
{
	return Vector4(x - value, y - value, z - value, w - value);

}

Vector4 Vector4::operator/(float value)
{
	return Vector4(x / value, y / value, z / value, w / value);

}


Vector4 Vector4::operator*(float value)
{

	return Vector4(x * value, y * value, z * value, w * value);
}













float Vector4::Norm() const
{
	float result = x * x + y * y + z * z+ w * w;

	return Math::FSqrtf(result) ;
}

Vector4 Vector4::Normalize() const
{
	float norm = Norm();

	Vector4 result = *this;

	result.x /= norm;
	result.y /= norm;
	result.z /= norm;
	result.w /= norm;



	return result;
}


Vector4::operator Vector() const
{
	Vector result = Vector(4);

	const float* data = &x;

	for (size_t i = 0; i < 4; i++)
	{
		result[i] = data[i];
	}

	return result;
}

Vector4::operator Vector2() const
{
	return Vector2(x, y);
}









float inline  Vector4::Angle(const Vector4& vec1, const Vector4& vec2)
{
	float dot = DotProduct(vec1, vec2);
	float normVec1 = vec1.Norm();
	float normVec2 = vec2.Norm();
	float angle = std::acos(dot / (normVec1 * normVec2));
	return angle;
}
std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << '\n';

	return stream;
}








