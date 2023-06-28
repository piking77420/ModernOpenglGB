#pragma once
#include <iostream>
#include "Vector3.h"


class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	float Norm() const;
	Vector4 Normalize() const;

	const float* GetPtr() const;

	float* SetPtr();



	float DotProduct(const Vector4& vec2) const;


	float DotProduct(const Vector4& vec1, const Vector4& vec2);


	float Angle(const Vector4& vec1, const Vector4& vec2);




	float operator[](const int& i) const;

	float& operator[](const int& i);

	Vector4 operator+(float value);
	Vector4 operator-(float value);
	Vector4 operator*(float value);
	Vector4 operator/(float value);



	Vector4(const Vector3& vec);

	Vector4(float _x, float _y, float _z, float _w);
	Vector4();
	~Vector4();

	static const Vector4 Zero;
	static const Vector4 One;


private:

};

std::ostream& operator<<(std::ostream& stream, const Vector4& vec);



inline Vector4 operator+(const Vector4& vec1, const Vector4& Row1)
{
	return Vector4(vec1.x + Row1.x, vec1.y + Row1.y, vec1.z + Row1.z, vec1.w + Row1.w);
}
inline Vector4 operator-(const Vector4& vec1, const Vector4& Row1)
{
	return Vector4(vec1.x - Row1.x, vec1.y - Row1.y, vec1.z - Row1.z , vec1.w - Row1.w);
}
inline Vector4 operator-(const Vector4& vec)
{
	return Vector4(-vec.x, -vec.y, -vec.z , -vec.w);
}
inline Vector4 operator*(const Vector4& vec1, const Vector4& Row1)
{
	return Vector4(vec1.x * Row1.x, vec1.y * Row1.y, vec1.z * Row1.z , vec1.w / Row1.w);
}
inline Vector4 operator/(const Vector4& vec1, const Vector4& Row1)
{
	return Vector4(vec1.x / Row1.x, vec1.y / Row1.y, vec1.z / Row1.z , vec1.w / Row1.w);
}

inline void operator+= (Vector4& vec1, const Vector4 Row1)
{
	vec1.x += Row1.x;
	vec1.y += Row1.y;
	vec1.z += Row1.z;
	vec1.w += Row1.w;

}
inline void operator-= (Vector4& vec1, const Vector4 Row1)
{
	vec1.x -= Row1.x;
	vec1.y -= Row1.y;
	vec1.z -= Row1.z;
	vec1.w -= Row1.w;

}
inline void operator*= (Vector4& vec1, const Vector4 Row1)
{
	vec1.x *= Row1.x;
	vec1.y *= Row1.y;
	vec1.z *= Row1.z;
}
inline void operator/= (Vector4& vec1, const Vector4 Row1)
{
	vec1.x /= Row1.x;
	vec1.y /= Row1.y;
	vec1.z /= Row1.z;
	vec1.w /= Row1.w;

}
inline Vector4 operator+(const Vector4& vec1, const float& value)
{
	Vector4 result = vec1;
	result.x += value;
	result.y += value;
	result.z += value;
	result.w += value;
	return result;
}
inline Vector4 operator*(const Vector4& vec1, const float& value)
{
	Vector4 result = vec1;
	result.x *= value;
	result.y *= value;
	result.z *= value;
	result.w *= value;
	return result;
}
inline Vector4 operator/(const Vector4& vec1, const float& value)
{
	Vector4 result = vec1;
	result.x /= value;
	result.y /= value;
	result.z /= value;
	result.w /= value;
	return result;
}
inline Vector4 operator-(const Vector4& vec1, const float& value)
{
	Vector4 result = vec1;
	result.x -= value;
	result.y -= value;
	result.z -= value;
	result.w -= value;
	return result;
}




inline bool operator!=(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z && vec1.w != vec2.w;
}

inline bool operator==(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}

inline bool operator<=(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x <= vec2.x && vec1.y <= vec2.y && vec1.z <= vec2.z && vec1.w <= vec2.w;
}

inline bool operator>=(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x >= vec2.x && vec1.y >= vec2.y && vec1.z >= vec2.z && vec1.w >= vec2.w;
}