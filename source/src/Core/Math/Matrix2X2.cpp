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
	
	result[0][0] = Columns[0].x;
	result[0][1] = Columns[0].y;

	result[1][0] = Columns[0].x;
	result[1][1] = Columns[0].y;
	
	return result;
}

Matrix2X2::operator Matrix3X3() const
{
	return  Matrix3X3((Vector3)Columns[0], (Vector3)Columns[1], Vector3::Zero());
}

Matrix2X2::operator Matrix4X4() const
{
	return Matrix4X4((Vector4)Columns[0], (Vector4)Columns[1], Vector3::Zero(), Vector3::Zero());
}


std::ostream& operator<<(std::ostream& stream ,Matrix2X2 matrix)
{
	stream << matrix.Columns[0].x << " " << matrix.Columns[1].x << ' \n ';

	stream << matrix.Columns[0].y << " " << matrix.Columns[1].y << ' \n ';

	return stream;
}

inline Matrix2X2 operator+(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Columns[0] = matrix1.Columns[0] + matrix2.Columns[0];
	result.Columns[1] = matrix1.Columns[1] + matrix2.Columns[1];

	return result;
}
inline Matrix2X2 operator-(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Columns[0] = matrix1.Columns[0] - matrix2.Columns[0];
	result.Columns[1] = matrix1.Columns[1] - matrix2.Columns[1];

	return result;
}
inline Matrix2X2 operator*(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	Matrix2X2 result;

	result.Columns[0].x = matrix1.Columns[0].x * matrix2.Columns[0].x + matrix1.Columns[1].y * matrix2.Columns[0].y;

	result.Columns[1].x = matrix1.Columns[0].x * matrix2.Columns[1].x + matrix1.Columns[1].y * matrix2.Columns[1].y;

	result.Columns[0].y = matrix1.Columns[0].y * matrix2.Columns[0].x + matrix1.Columns[1].y * matrix2.Columns[0].y;

	result.Columns[1].y = matrix1.Columns[0].y * matrix2.Columns[1].x + matrix1.Columns[1].y * matrix2.Columns[1].y;


	return result;
}

static Matrix2X2 RotationMatrix2X2(const float& angle)
{
	Matrix2X2 NewMatrix;

	NewMatrix.Columns[0].x = cosf(Math::Rad2Deg * angle);
	NewMatrix.Columns[0].y = -sinf(Math::Rad2Deg * angle);

	NewMatrix.Columns[1].x = sinf(Math::Rad2Deg * angle);
	NewMatrix.Columns[1].y = cosf(Math::Rad2Deg * angle);

	return NewMatrix;
}
static inline Matrix2X2 operator-(const Matrix2X2& matrix2)
{
	Matrix2X2 result = matrix2;

	result.Columns[0].x = -result.Columns[0].x;
	result.Columns[0].y = -result.Columns[0].y;

	result.Columns[1].x = -result.Columns[1].x;
	result.Columns[1].y = -result.Columns[1].y;

	return result;
}

static Matrix2X2 RotationMatrix2X2At(const Vector2& RotatePoint, const float& angle)
{

}
static inline Matrix2X2 operator*(float value, const Matrix2X2& matrix1)
{
	Matrix2X2 result = matrix1;

	result.Columns[0].x *= value;
	result.Columns[0].y *= value;

	result.Columns[1].x *= value;
	result.Columns[1].y *= value;

	return result;
}

std::ostream& operator<<(std::ostream& stream, const Matrix2X2& matrix)
{
	stream << matrix.Columns[0].x << " " << matrix.Columns[1].x << " ";
	stream << '\n';
	stream << matrix.Columns[0].y << " " << matrix.Columns[1].y << " ";
	stream << '\n';

	return stream;
}