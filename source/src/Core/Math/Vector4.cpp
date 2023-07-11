#include "Vector4.h"
#include "Vector3.h"
#include "Vector.h"
#include "Vector2.h"
#include "Mathf.h"

const Vector4 Vector4::Zero = Vector4(0,0,0,0);
const Vector4 Vector4::One = Vector4(1, 1, 1, 1);




float Vector4::operator[](int i) const
{
	assert(i >= 0 && i < 4);
	const float* data = &x;
	return data[i];
}

float& Vector4::operator[](int i)
{
	assert(i >= 0 && i < 4);
	float* data = &x;
	return data[i];
}


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
Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{
}









Vector4::Vector4(const Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = 1;

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

Vector4::operator Vector3() const
{
	return Vector3(x,y,z);
}








float Vector4::Angle(const Vector4& vec1, const Vector4& vec2)
{
	float dot = DotProduct(vec1, vec2);
	float normVec1 = vec1.Norm();
	float normVec2 = vec2.Norm();
	float angle = std::acosf(dot / (normVec1 * normVec2));
	return angle;
}
std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << '\n';

	return stream;
}








