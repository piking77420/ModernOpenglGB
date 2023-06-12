#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4X4.h"


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
	Vector returnVector = Vector(x,y,z);

	return returnVector;
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

Vector3::Vector3(float _x , float  _y , float _z) : x(_x), y(_y), z(_z)
{
}

Vector3::Vector3() : x(0) , y(0) , z(0)
{
}

Vector3::~Vector3()
{
}

float* Vector3::SetPtr()
{
	return &x;
}

const  float* Vector3::GetPtr() const
{
	return &x;
}

float Vector3::Norm() const
{

	return sqrt(powf(x,2) + powf(y,2) + powf(z,2));
}

Vector3 Vector3::Normalize() const
{
	float norm = Norm();

	if (norm == 1.f)
		return *this;

	return Vector3( x/norm ,y/norm ,z/norm);
}

Vector3 Vector3::Normal(const Vector3& vector) const
{
	return CrossProduct(vector);
}

Vector3 Vector3::Reflect(const Vector3& Vector, const Vector3& Normals)
{
	Vector3 result = Vector3(0, 0, 0);
	Vector3 NoramizeNormal = Normals.Normalize();

	result = Vector - (NoramizeNormal * (2.f * (DotProduct(Vector, Normals))));

	return result;
}

float Vector3::DotProduct(const Vector3& Row0) const
{
	return x * Row0.x + y * Row0.y + z * Row0.z;
}

Vector3 Vector3::CrossProduct(const Vector3& Row0) const
{
	return Vector3(y * Row0.z - z * Row0.y,
		z * Row0.x - x * Row0.z,
		x * Row0.y - y * Row0.x);
}

float Vector3::DotProduct(const Vector3& vec1, const Vector3& Row1)
{
	return vec1.DotProduct(Row1);
}

Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
{
	return a.CrossProduct(b);
}

float Vector3::Angle(const Vector3& vec1, const Vector3& Row1)
{
	return  acosf(DotProduct(vec1,Row1) / (vec1.Norm() * Row1.Norm()));
}



// good
Vector3 Vector3::CylinderToCoordianteCartisiant(float _radius, float angle, float zCoordinate)
{


	Vector3 result;
	result.x = _radius * cosf(angle);
	result.y = _radius * sinf(angle);
	result.z = zCoordinate;

	return result;
}

Vector3 Vector3::CartisianeCoorToCylinderCoor()
{
	

	Vector3 result;
	result.x = sqrtf( x * x + y * y   ); 
	result.y = atan2f(y , x);
	result.z = z;

	return result;

}


Vector3 Vector3::ToSphericalCoordiant(float _radius, float _Beta, float _Teta)
{
	return Vector3(_radius * sinf(_Beta) * cosf(_Teta), _radius * sinf(_Beta) * sinf(_Teta), _radius * cosf(_Beta));
}

Vector3 Vector3::ToRadian()
{
	return Vector3(degreesToRadians(x),degreesToRadians(y),degreesToRadians(z));
}





std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " <<'\n';

	return stream;
}
