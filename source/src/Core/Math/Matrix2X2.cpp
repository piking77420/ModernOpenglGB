#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"
#include "Matrix3X3.h"
#include "Matrix.h"
#include "ToolBoxMathHeaders.h"








Matrix2X2 Matrix2X2::RotationMatrix2X2(float angle)
{
	return Matrix2X2(std::cosf(angle),-std::sinf(angle), std::sinf(angle), std::cosf(angle));
}



Matrix2X2::operator Matrix() const 
{
	Matrix result = Matrix(2);
	
	result[0][0] = Coloms[0].x;
	result[0][1] = Coloms[0].y;

	result[1][0] = Coloms[0].x;
	result[1][1] = Coloms[0].y;
	
	return result;
}

Matrix2X2::operator Matrix3X3() const
{
	return  Matrix3X3((Vector3)Coloms[0], (Vector3)Coloms[1], Vector3::Zero());
}

Matrix2X2::operator Matrix4X4() const
{
	return Matrix4X4((Vector4)Coloms[0], (Vector4)Coloms[1], Vector3::Zero(), Vector3::Zero());
}


std::ostream& operator<<(std::ostream& stream ,Matrix2X2 matrix)
{
	stream << matrix.Coloms[0].x << " " << matrix.Coloms[1].x << ' \n ';

	stream << matrix.Coloms[0].y << " " << matrix.Coloms[1].y << ' \n ';

	return stream;
}

inline Matrix2X2 operator+(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Coloms[0] = matrix1.Coloms[0] + matrix2.Coloms[0];
	result.Coloms[1] = matrix1.Coloms[1] + matrix2.Coloms[1];



	return result;
}
inline Matrix2X2 operator-(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Coloms[0] = matrix1.Coloms[0] - matrix2.Coloms[0];
	result.Coloms[1] = matrix1.Coloms[1] - matrix2.Coloms[1];



	return result;
}
inline Matrix2X2 operator*(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{

	Matrix2X2 result;

	result.Coloms[0].x = matrix1.Coloms[0].x * matrix2.Coloms[0].x + matrix1.Coloms[1].y * matrix2.Coloms[0].y;

	result.Coloms[1].x = matrix1.Coloms[0].x * matrix2.Coloms[1].x + matrix1.Coloms[1].y * matrix2.Coloms[1].y;

	result.Coloms[0].y = matrix1.Coloms[0].y * matrix2.Coloms[0].x + matrix1.Coloms[1].y * matrix2.Coloms[0].y;

	result.Coloms[1].y = matrix1.Coloms[0].y * matrix2.Coloms[1].x + matrix1.Coloms[1].y * matrix2.Coloms[1].y;


	return result;

}

static Matrix2X2 RotationMatrix2X2(const float& angle)
{
	Matrix2X2 NewMatrix;


	NewMatrix.Coloms[0].x = cosf(Math::Rad2Deg * angle);
	NewMatrix.Coloms[0].y = -sinf(Math::Rad2Deg * angle);

	NewMatrix.Coloms[1].x = sinf(Math::Rad2Deg * angle);
	NewMatrix.Coloms[1].y = cosf(Math::Rad2Deg * angle);




	return NewMatrix;
}
static inline Matrix2X2 operator-(const Matrix2X2& matrix2)
{
	Matrix2X2 result = matrix2;

	result.Coloms[0].x = -result.Coloms[0].x;
	result.Coloms[0].y = -result.Coloms[0].y;

	result.Coloms[1].x = -result.Coloms[1].x;
	result.Coloms[1].y = -result.Coloms[1].y;

	return result;

}

static Matrix2X2 RotationMatrix2X2At(const Vector2& RotatePoint, const float& angle)
{

}
static inline Matrix2X2 operator*(float value, const Matrix2X2& matrix1)
{
	Matrix2X2 result = matrix1;


	result.Coloms[0].x *= value;
	result.Coloms[0].y *= value;

	result.Coloms[1].x *= value;
	result.Coloms[1].y *= value;


	return result;

}

std::ostream& operator<<(std::ostream& stream, const Matrix2X2& matrix)
{
	stream << matrix.Coloms[0].x << " " << matrix.Coloms[1].x << " ";
	stream << '\n';
	stream << matrix.Coloms[0].y << " " << matrix.Coloms[1].y << " ";
	stream << '\n';

	return stream;
}