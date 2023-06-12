#include "Matrix2X2.h"
#include "Matrix.h"
#include "Vector.h"
#include "Mathf.h"




Matrix2X2::Matrix2X2(Vector2 _vec, Vector2 _vec2) 
{

	Rows[0] = _vec;
	Rows[1] = _vec2;
}

Matrix2X2 Matrix2X2::Identity()
{
	Matrix2X2 result;

	result.Rows[0].x = 1;
	result.Rows[0].y = 0;
	result.Rows[1].x = 0;
	result.Rows[1].y = 1;

	return result;
}


Matrix2X2::Matrix2X2(float x1 , float y1 , float x2 , float y2)
	
{
	Rows[0].x = x1;
	Rows[0].y = y2;


	Rows[1].x = x1;
	Rows[1].x = y2;

}

Matrix2X2::Matrix2X2()
{
}

Matrix2X2::~Matrix2X2()
{
}

Matrix2X2::operator Matrix() const 
{
	Matrix result = Matrix(4);
	/*
	
	
	result.mData[0].data[0] = Row0.x;
	result.mData[0].data[1] = Row0.y;

	result.mData[1].data[0] = Row1.x;
	result.mData[1].data[1] = Row1.y;
	*/
	return result;
}


std::ostream& operator<<(std::ostream& stream ,Matrix2X2 matrix)
{
	stream << matrix.Rows[0].x << " " << matrix.Rows[1].x << ' \n ';

	stream << matrix.Rows[0].y << " " << matrix.Rows[1].y << ' \n ';

	return stream;
}

inline Matrix2X2 operator+(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Rows[0] = matrix1.Rows[0] + matrix2.Rows[0];
	result.Rows[1] = matrix1.Rows[1] + matrix2.Rows[1];



	return result;
}
inline Matrix2X2 operator-(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Rows[0] = matrix1.Rows[0] - matrix2.Rows[0];
	result.Rows[1] = matrix1.Rows[1] - matrix2.Rows[1];



	return result;
}
inline Matrix2X2 operator*(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{

	Matrix2X2 result;

	result.Rows[0].x = matrix1.Rows[0].x * matrix2.Rows[0].x + matrix1.Rows[1].x + matrix2.Rows[0].y;

	result.Rows[1].x = matrix1.Rows[0].x * matrix2.Rows[1].x + matrix1.Rows[1].x + matrix2.Rows[1].y;

	result.Rows[0].y = matrix1.Rows[0].y * matrix2.Rows[0].x + matrix1.Rows[1].y + matrix2.Rows[0].y;

	result.Rows[1].y = matrix1.Rows[0].y * matrix2.Rows[1].x + matrix1.Rows[1].y + matrix2.Rows[1].y;


	return result;

}

static Matrix2X2 RotationMatrix2X2(const float& angle)
{
	Matrix2X2 NewMatrix;


	NewMatrix.Rows[0].x = cosf(degreesToRadians(angle));
	NewMatrix.Rows[0].y = -sinf(degreesToRadians(angle));

	NewMatrix.Rows[1].x = sinf(degreesToRadians(angle));
	NewMatrix.Rows[1].y = cosf(degreesToRadians(angle));


	return NewMatrix;
}
static inline Matrix2X2 operator-(const Matrix2X2& matrix2)
{
	Matrix2X2 result = matrix2;

	result.Rows[0].x = -result.Rows[0].x;
	result.Rows[0].y = -result.Rows[0].y;

	result.Rows[1].x = -result.Rows[1].x;
	result.Rows[1].y = -result.Rows[1].y;

	return result;

}
static Matrix2X2 RotationMatrix2X2At(const Vector2& RotatePoint, const float& angle)
{

}
static inline Matrix2X2 operator*(float value, const Matrix2X2& matrix1)
{
	Matrix2X2 result = matrix1;


	result.Rows[0].x *= value;
	result.Rows[0].y *= value;

	result.Rows[1].x *= value;
	result.Rows[1].y *= value;


	return result;

}
