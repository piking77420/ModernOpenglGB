#pragma once
#include <iostream>
#include "Vector2.h"

class Vector;
class Vector4;


class Vector3
{
public:

	float x; 
	float y;
	float z;

	float* SetPtr() ;

	const  float* GetPtr() const ;

	float Norm() const;
	Vector3 Normalize() const;
	Vector3 Normal(const Vector3& vector) const;

	Vector3 Reflect(const Vector3& Vector, const Vector3& Normals);

	float DotProduct(const Vector3& Row0 ) const;

	Vector3 CrossProduct(const Vector3& Row0) const;


	float DotProduct(const Vector3& vec1, const Vector3& Row1);

	Vector3 CrossProduct(const Vector3& a, const Vector3& b);

	float Angle(const Vector3& vec1, const Vector3& Row1);


	Vector3 CartisianeCoorToCylinderCoor();
	Vector3 CylinderToCoordianteCartisiant(float _radius, float angle, float zCoordinate);

	Vector3 ToSphericalCoordiant(float _radius, float _Angle, float _Teta);

	Vector3 ToRadian();

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 Right;
	static const Vector3 Left;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Forward;
	static const Vector3 BackForward;

	




	

	explicit operator Vector2() const;
	explicit operator Vector() const;

	Vector3(const Vector4& vec);
	Vector3(float _x, float _y, float _z);
	Vector3();
	~Vector3();

private:

	


};





 inline Vector3 operator+(const Vector3& vec1 , const Vector3& Row1)
{
	return Vector3(vec1.x + Row1.x, vec1.y + Row1.y, vec1.z + Row1.z);
}
 inline Vector3 operator-(const Vector3& vec1, const Vector3& Row1)
{
	return Vector3(vec1.x - Row1.x, vec1.y - Row1.y, vec1.z - Row1.z);
}
 inline Vector3 operator-(const Vector3& vec)
 {	
	 return Vector3(-vec.x , -vec.y , -vec.z);
 }
 inline Vector3 operator*(const Vector3& vec1, const Vector3& Row1)
{
	return Vector3(vec1.x * Row1.x, vec1.y * Row1.y, vec1.z * Row1.z);
}
 inline Vector3 operator/(const Vector3& vec1, const Vector3& Row1)
{
	return Vector3(vec1.x / Row1.x, vec1.y / Row1.y, vec1.z / Row1.z);
}

 inline void operator+= (Vector3& vec1, const Vector3 Row1)
 {
	 vec1.x += Row1.x;
	 vec1.y += Row1.y;
	 vec1.z += Row1.z;
 }
 inline void operator-= (Vector3& vec1, const Vector3 Row1)
 {
	 vec1.x -= Row1.x;
	 vec1.y -= Row1.y;
	 vec1.z -= Row1.z;
 }
 inline void operator*= (Vector3& vec1, const Vector3 Row1)
 {
	 vec1.x *= Row1.x;
	 vec1.y *= Row1.y;
	 vec1.z *= Row1.z;
 }
 inline void operator/= (Vector3& vec1, const Vector3 Row1)
{
	vec1.x /= Row1.x;
	vec1.y /= Row1.y;
	vec1.z /= Row1.z;
}
 inline Vector3 operator+(const Vector3& vec1, const float& value)
 {
	 Vector3 result = vec1;
	 result.x += value;
	 result.y += value;
	 result.z += value;
	 return result;
 }
 inline Vector3 operator*(const Vector3& vec1, const float& value)
 {
	 Vector3 result = vec1;
	 result.x *= value;
	 result.y *= value;
	 result.z *= value;
	 return result;
 }
 inline Vector3 operator/(const Vector3& vec1, const float& value)
 {
	 Vector3 result = vec1;
	 result.x /= value;
	 result.y /= value;
	 result.z /= value;
	 return result;
 }
 inline Vector3 operator-(const Vector3& vec1, const float& value)
 {
	 Vector3 result = vec1;
	 result.x -= value;
	 result.y -= value;
	 result.z -= value;
	 return result;
 }

 inline Vector3 operator*=(const Vector3& vec1, const float& value)
 {
	 Vector3 result = vec1;
	 result.x *= value;
	 result.y *= value;
	 result.z *= value;
	 return result;
 }

 inline bool operator!=(const Vector3& vec1 , const Vector3& vec2)
 {
	 return (vec1.x != vec2.x) || (vec1.y != vec2.y )|| (vec1.z != vec2.z);
 }

 inline bool operator==(const Vector3& vec1, const Vector3& vec2)
 {
	 return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
 }

 inline bool operator<=(const Vector3& vec1, const Vector3& vec2)
 {
	 return vec1.x <= vec2.x && vec1.y <= vec2.y && vec1.z <= vec2.z;
 }

 inline bool operator<(const Vector3& vec1, const Vector3& vec2)
 {
	 return vec1.x < vec2.x && vec1.y < vec2.y && vec1.z < vec2.z;
 }

 inline bool operator>(const Vector3& vec1, const Vector3& vec2)
 {
	 return vec1.x > vec2.x && vec1.y > vec2.y && vec1.z > vec2.z;
 }

 inline bool operator>=(const Vector3& vec1, const Vector3& vec2)
 {
	 return vec1.x >= vec2.x && vec1.y >= vec2.y && vec1.z >= vec2.z;
 }

 inline Vector3 operator/(const float value, const Vector3& Row1)
 {
	 return Vector3(value / Row1.x, value / Row1.y, value / Row1.z);
 }


 inline void operator+= (Vector3& vec1, const Vector2 Row1)
 {
	 vec1.x += Row1.x;
	 vec1.y += Row1.y;
 }
 inline void operator-= (Vector3& vec1, const Vector2 Row1)
 {
	 vec1.x -= Row1.x;
	 vec1.y -= Row1.y;
 }

 inline void operator*= (Vector3& vec1, const Vector2 Row1)
 {
	 vec1.x *= Row1.x;
	 vec1.y *= Row1.y;
 }
 inline void operator/= (Vector3& vec1, const Vector2 Row1)
 {
	 vec1.x /= Row1.x;
	 vec1.y /= Row1.y;
 }


std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
static inline Vector3 Lerp(Vector3 startValue, Vector3 endValue, float prt)
{
	return (startValue + (endValue - startValue) * prt);
}