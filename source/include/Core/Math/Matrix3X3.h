#pragma once
#include "Matrix2X2.h"
#include "Vector3.h"
#include "Matrix.h"


class Matrix3X3
{
public:


	Vector3 Ligns[3];



	Matrix3X3 TranslationMatrix3X3(const Vector2& translation);
	Matrix3X3 Rotation2DMatrix3X3(const float& angle);





	Matrix3X3 Identity();
	Matrix3X3(const Vector3& a , const Vector3& b, const Vector3& c);
	Matrix3X3 operator*(const Matrix3X3& matrix);

	Vector3 operator[](const int& i) const;



	explicit operator Matrix();

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
