#pragma once
#include <iostream>
#include "Vector4.h"
#include "Matrix3X3.h"

class Vector3;
class Matrix;
class Quaternion;

class Matrix4X4
{
public:

	Vector4 Colums[4];



	inline Vector3 GetPos();
	
	static Matrix4X4 ScalingMatrix4X4(const Vector3& ScalingFactor);

	// rad
	static Matrix4X4 RotationZ4X4(const float& angle);

	// rad
	static Matrix4X4 RotationY4X4(const float& angle);

	// rad
	static Matrix4X4 RotationX4X4(const float& angle);


	// rad
	static Matrix4X4 RotationMatrix4X4(const Vector3& angle);

	static Matrix4X4 TranslateMatrix4X4(const Vector3& translation);


	constexpr inline static Matrix4X4 Identity()
	{
		Matrix4X4 result;

		result.Colums[0].x = 1;
		result.Colums[0].y = 0;
		result.Colums[0].z = 0;
		result.Colums[0].w = 0;

		result.Colums[1].x = 0;
		result.Colums[1].y = 1;
		result.Colums[1].z = 0;
		result.Colums[1].w = 0;

		result.Colums[2].x = 0;
		result.Colums[2].y = 0;
		result.Colums[2].z = 1;
		result.Colums[2].w = 0;

		result.Colums[3].x = 0;
		result.Colums[3].y = 0;
		result.Colums[3].z = 0;
		result.Colums[3].w = 1;


		return result;
	}

	Matrix4X4 Invert();
	Matrix4X4 Transposate() const;
	float Determinant() const;

	constexpr inline const float* GetPtr() const
	{
		return &Colums[0].x;
	}
	constexpr inline float* SetPtr()
	{
		return &Colums[0].x;
	}


	static inline Matrix4X4 AdjoinMatrix(const Matrix4X4& matrix);
	

	Matrix4X4 operator*(const Matrix4X4& matrix) const;
	Vector4 operator[](const int& i ) const ;
	Vector4& operator[](const int& i) ;
	explicit operator Matrix();


	constexpr Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
	{
		Colums[0] = a;
		Colums[1] = b;
		Colums[2] = c;
		Colums[3] = d;
	}
	constexpr Matrix4X4() = default;
	

private:

};

 Vector4 operator*(const Matrix4X4& matrix, const Vector4& Row1);
 Vector4 operator*(const Vector4& Row1,const Matrix4X4& matrix);

std::ostream& operator<<(std::ostream& stream, const  Matrix4X4& maxtrix);
