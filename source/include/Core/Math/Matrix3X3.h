#pragma once
#include "Vector3.h"
#include "Matrix.h"
#include "Vector.h"
#include "Matrix2X2.h"

class Matrix3X3
{
public:


	Vector3 Coloms[3];
	static Matrix3X3 Identity();

	

	[[nodiscard]]
	static Matrix3X3 TranslationMatrix3X3(const Vector2& translation);
	[[nodiscard]]
	static Matrix3X3 Rotation2DMatrix3X3(const float& angle);
	[[nodiscard]]
	Matrix3X3 Invert();
	[[nodiscard]]
	constexpr inline Matrix3X3 Transposate() const
	{
		Matrix3X3 result;


		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				result[x][y] = Coloms[y][x];
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

		Matrix3X3 copy = matrix.Transposate();
		Matrix3X3 minor;

		minor.Coloms[0][0] = Matrix2X2::Determinant(Matrix2X2(copy[1].y, copy[1].z, copy[2].y, copy[2].z));
		minor.Coloms[0][1] = -Matrix2X2::Determinant(Matrix2X2(copy[1].x, copy[1].z, copy[2].x, copy[2].z));
		minor.Coloms[0][2] = Matrix2X2::Determinant(Matrix2X2(copy[1].x, copy[1].y, copy[2].x, copy[2].y));

		minor.Coloms[1][0] = -Matrix2X2::Determinant(Matrix2X2(copy[0].y, copy[0].z, copy[2].y, copy[2].z));
		minor.Coloms[1][1] = Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].z, copy[2].x, copy[2].z));
		minor.Coloms[1][2] = -Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].y, copy[2].x, copy[2].y));

		minor.Coloms[2][0] = Matrix2X2::Determinant(Matrix2X2(copy[0].y, copy[0].z, copy[1].y, copy[1].z));
		minor.Coloms[2][1] = -Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].z, copy[1].x, copy[1].z));
		minor.Coloms[2][2] = Matrix2X2::Determinant(Matrix2X2(copy[0].x, copy[0].y, copy[1].x, copy[1].y));




		return minor;
	}

	
	
	constexpr inline Vector3& operator[](const int& i)
	{
		return Coloms[i];
	}
	constexpr inline const Vector3& operator[](const int& i) const
	{
		return Coloms[i];
	}


	explicit operator Matrix();


	[[nodiscard]]
	constexpr const float* GetPtr() const
	{
		return &Coloms[0].x;
	}
	[[nodiscard]]
	constexpr float* SetPtr()
	{
		return &Coloms[0].x;
	}

	constexpr Matrix3X3(const Vector3& a, const Vector3& b, const Vector3& c)
	{
		Coloms[0] = a;
		Coloms[1] = b;
		Coloms[2] = c;
	}
	constexpr Matrix3X3() = default;





	constexpr Matrix3X3 operator*(const float value) const
	{
		Matrix3X3 result = *this;

		result.Coloms[0].x *= value;
		result.Coloms[0].y *= value;
		result.Coloms[0].z *= value;


		result.Coloms[1].x *= value;
		result.Coloms[1].y *= value;
		result.Coloms[1].z *= value;

		result.Coloms[2].x *= value;
		result.Coloms[2].y *= value;
		result.Coloms[2].z *= value;



		return result;
	}

	Matrix3X3 operator*(const Matrix3X3& matrix) const 
	{
		Matrix3X3 result;

		result.Coloms[0].x = this->Coloms[0].x * matrix[0].x + this->Coloms[0].y * matrix[1].x + this->Coloms[0].z * matrix[2].x;
		result.Coloms[0].y = this->Coloms[0].x * matrix[0].y + this->Coloms[0].y * matrix[1].y + this->Coloms[0].z * matrix[2].y;
		result.Coloms[0].z = this->Coloms[0].x * matrix[0].z + this->Coloms[0].y * matrix[1].z + this->Coloms[0].z * matrix[2].z;

		result.Coloms[1].x = this->Coloms[1].x * matrix[0].x + this->Coloms[1].y * matrix[1].x + this->Coloms[1].z * matrix[2].x;
		result.Coloms[1].y = this->Coloms[1].x * matrix[0].y + this->Coloms[1].y * matrix[1].y + this->Coloms[1].z * matrix[2].y;
		result.Coloms[1].z = this->Coloms[1].x * matrix[0].z + this->Coloms[1].y * matrix[1].z + this->Coloms[1].z * matrix[2].z;

		result.Coloms[2].x = this->Coloms[2].x * matrix[0].x + this->Coloms[2].y * matrix[1].x + this->Coloms[2].z * matrix[2].x;
		result.Coloms[2].y = this->Coloms[2].x * matrix[0].y + this->Coloms[2].y * matrix[1].y + this->Coloms[2].z * matrix[2].y;
		result.Coloms[2].z = this->Coloms[2].x * matrix[0].z + this->Coloms[2].y * matrix[1].z + this->Coloms[2].z * matrix[2].z;


		return result;
	}


private:

};




std::ostream& operator<<(std::ostream& stream, const  Matrix3X3& maxtrix);
