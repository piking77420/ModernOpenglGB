#pragma once
#include "Vector3.h"
#include "Matrix.h"
#include "Vector.h"
#include "Matrix2X2.h"

class Matrix3X3
{
public:


	Vector3 Columns[3];
	static Matrix3X3 Identity();

	

	[[nodiscard]]
	static Matrix3X3 TranslationMatrix3X3(const Vector2& translation);
	[[nodiscard]]
	static Matrix3X3 Rotation2DMatrix3X3(const float& angle);
	[[nodiscard]]
	Matrix3X3 Invert();
	[[nodiscard]]
	constexpr inline Matrix3X3 Transpose() const
	{
		Matrix3X3 result;


		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				result[x][y] = Columns[y][x];
			}
		}


		return result;
	}

	

	constexpr inline static float Determinant(const Matrix3X3& matrix)
	{
		float result = 0;

		float d0 = Matrix2X2::Determinant(Matrix2X2(matrix[1].y, matrix[1].z, matrix[2].y, matrix[2].z));

		float d1 = Matrix2X2::Determinant(Matrix2X2(matrix[1].x, matrix[1].z, matrix[2].x, matrix[2].z));

		float d2 = Matrix2X2::Determinant(Matrix2X2(matrix[1].x, matrix[1].y, matrix[2].x, matrix[2].y));

		float m0 = +1 * matrix[0].x * d0;
		float m1 = -1 * matrix[0].y * d1;
		float m2 = +1 * matrix[0].z * d2;

		result = m0 + m1 + m2;

		return result;

	}

	static inline Matrix3X3 AdjoinMatrix(const Matrix3X3& matrix)
	{

		Matrix3X3 copy = matrix.Transpose();
		Matrix3X3 minor;

		minor.Columns[0][0] = Matrix2X2::Determinant(Matrix2X2(copy[1].y, copy[1].z, copy[2].y, copy[2].z));
		minor.Columns[0][1] = -Matrix2X2::Determinant(Matrix2X2(copy[1].x, copy[1].z, copy[2].x, copy[2].z));
		minor.Columns[0][2] = Matrix2X2::Determinant(Matrix2X2(copy[1].x, copy[1].y, copy[2].x, copy[2].y));

		minor.Columns[1][0] = -Matrix2X2::Determinant(Matrix2X2(copy[0].y, copy[0].z, copy[2].y, copy[2].z));
		minor.Columns[1][1] = Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].z, copy[2].x, copy[2].z));
		minor.Columns[1][2] = -Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].y, copy[2].x, copy[2].y));

		minor.Columns[2][0] = Matrix2X2::Determinant(Matrix2X2(copy[0].y, copy[0].z, copy[1].y, copy[1].z));
		minor.Columns[2][1] = -Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].z, copy[1].x, copy[1].z));
		minor.Columns[2][2] = Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].y, copy[1].x, copy[1].y));




		return minor;
	}

	
	
	constexpr inline Vector3& operator[](const int& i)
	{
		return Columns[i];
	}
	constexpr inline const Vector3& operator[](const int& i) const
	{
		return Columns[i];
	}


	constexpr inline float Trace()
	{
		Matrix3X3& m = *this;
		return m[0][0] + m[1][1] + m[2][2];
	}

	explicit operator Matrix();


	[[nodiscard]]
	constexpr const float* GetPtr() const
	{
		return &Columns[0].x;
	}
	[[nodiscard]]
	constexpr float* SetPtr()
	{
		return &Columns[0].x;
	}

	constexpr Matrix3X3(const Vector3& a, const Vector3& b, const Vector3& c)
	{
		Columns[0] = a;
		Columns[1] = b;
		Columns[2] = c;
	}
	constexpr Matrix3X3() = default;





	constexpr Matrix3X3 operator*(const float value) const
	{
		Matrix3X3 result = *this;

		result.Columns[0].x *= value;
		result.Columns[0].y *= value;
		result.Columns[0].z *= value;


		result.Columns[1].x *= value;
		result.Columns[1].y *= value;
		result.Columns[1].z *= value;

		result.Columns[2].x *= value;
		result.Columns[2].y *= value;
		result.Columns[2].z *= value;



		return result;
	}

	Matrix3X3 operator*(const Matrix3X3& matrix) const 
	{
		Matrix3X3 result;

		result.Columns[0].x = this->Columns[0].x * matrix[0].x + this->Columns[0].y * matrix[1].x + this->Columns[0].z * matrix[2].x;
		result.Columns[0].y = this->Columns[0].x * matrix[0].y + this->Columns[0].y * matrix[1].y + this->Columns[0].z * matrix[2].y;
		result.Columns[0].z = this->Columns[0].x * matrix[0].z + this->Columns[0].y * matrix[1].z + this->Columns[0].z * matrix[2].z;

		result.Columns[1].x = this->Columns[1].x * matrix[0].x + this->Columns[1].y * matrix[1].x + this->Columns[1].z * matrix[2].x;
		result.Columns[1].y = this->Columns[1].x * matrix[0].y + this->Columns[1].y * matrix[1].y + this->Columns[1].z * matrix[2].y;
		result.Columns[1].z = this->Columns[1].x * matrix[0].z + this->Columns[1].y * matrix[1].z + this->Columns[1].z * matrix[2].z;

		result.Columns[2].x = this->Columns[2].x * matrix[0].x + this->Columns[2].y * matrix[1].x + this->Columns[2].z * matrix[2].x;
		result.Columns[2].y = this->Columns[2].x * matrix[0].y + this->Columns[2].y * matrix[1].y + this->Columns[2].z * matrix[2].y;
		result.Columns[2].z = this->Columns[2].x * matrix[0].z + this->Columns[2].y * matrix[1].z + this->Columns[2].z * matrix[2].z;


		return result;
	}


private:

};




std::ostream& operator<<(std::ostream& stream, const  Matrix3X3& maxtrix);
