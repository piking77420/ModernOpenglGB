#pragma once
#include "Vector3.h"
#include "Matrix.h"
#include "Vector.h"
#include "Matrix2X2.h"

class Matrix3X3
{
public:


	Vector3 Coloms[3];
	Matrix3X3 Identity() const;


	[[nodiscard]]
	static Matrix3X3 TranslationMatrix3X3(const Vector2& translation);
	[[nodiscard]]
	static Matrix3X3 Rotation2DMatrix3X3(const float& angle);
	[[nodiscard]]
	Matrix3X3 Invert();
	[[nodiscard]]
	Matrix3X3 Transposate() const ;
	
	Vector3& operator[](const int& i);
	const Vector3& operator[](const int& i) const;
	Matrix3X3 operator*(const Matrix3X3& matrix);	
	explicit operator Matrix();

	[[nodiscard]]
	const float* GetPtr() const;
	[[nodiscard]]
	float* SetPtr();

	Matrix3X3(const Vector3& a, const Vector3& b, const Vector3& c);
	Matrix3X3();
	~Matrix3X3();

private:

};

Matrix3X3 operator+(const Matrix3X3& max , const Matrix2X2& max1);
Matrix3X3 operator+(const Matrix2X2& max, const Matrix3X3& max1);
Matrix3X3 operator+(const Matrix3X3& max, const Matrix3X3& max1);
Matrix3X3 operator-(const Matrix3X3& max, const Matrix3X3& max1);
Matrix3X3 operator-(const Matrix2X2& max, const Matrix3X3& max1);
Matrix3X3 operator-(const Matrix3X3& max, const Matrix2X2& max1);
Matrix3X3 operator*(const float& value , const Matrix2X2& max );


std::ostream& operator<<(std::ostream& stream, const  Matrix3X3& maxtrix);
