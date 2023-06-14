#include <iostream>
#include "Vector2.h"



#pragma once

class Matrix;

class Matrix2X2
{
public:


	Vector2 Ligns[2];




	 Matrix2X2 RotationMatrix2X2(const float& angle);

	//static Matrix2X2 RotationMatrix2X2At(const Vector2& RotatePoint, const float& angle);



	Matrix2X2 Identity();
	Matrix2X2(float x1, float y1, float x2, float y2);
	Matrix2X2(Vector2 Row0 , Vector2 Row1);
	Matrix2X2();
	~Matrix2X2();


	explicit operator Matrix() const;

private:

};


inline Matrix2X2 operator+(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator-(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator*(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator*(float value, const Matrix2X2& matrix1);

inline Matrix2X2 operator-(const Matrix2X2& matrix2);



//std::ostream& operator<<(Matrix2X2 matrix);