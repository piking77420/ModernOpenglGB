#pragma once
#include <iostream>
#include"Vector2.h"



class Matrix;
class Matrix3X3;

class Matrix2X2
{
public:


	Vector2 Coloms[2];

	static const Matrix2X2 Identity;


	[[nosdiscard]]
	static Matrix2X2 RotationMatrix2X2(float angle);

	explicit operator Matrix() const;
	explicit operator Matrix3X3() const;
	explicit operator Matrix4X4() const;


	Matrix2X2(float x1, float y1, float x2, float y2);
	Matrix2X2(Vector2 Row0 , Vector2 Row1);
	Matrix2X2();
	~Matrix2X2();




private:

};


inline Matrix2X2 operator+(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator-(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator*(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator*(float value, const Matrix2X2& matrix1);

inline Matrix2X2 operator-(const Matrix2X2& matrix2);



std::ostream& operator<<(std::ostream& stream,const Matrix2X2& matrix);