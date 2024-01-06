#pragma once
#include <iostream>
#include"Vector2.h"



class Matrix;
class Matrix3X3;
class Matrix4X4;

class Matrix2X2
{
public:


	Vector2 Columns[2];


	constexpr inline static float Determinant(Matrix2X2 matrix)
	{
		float result = 0;

		result = matrix.Columns[0].x * matrix.Columns[1].y - matrix.Columns[0].y * matrix.Columns[1].x;

		return result;

	}

	constexpr static int Size()
	{
		return 4;
	}

	
	static Matrix2X2 RotationMatrix2X2(float angle);
	
	constexpr const float* GetPtr() const
	{
		return &Columns[0].x;
	}

	constexpr float* SetPtr() 
	{
		return &Columns[0].x;
	}


	constexpr Matrix2X2(float x1, float y1, float x2, float y2)
	{
		Columns[0].x = x1;
		Columns[0].y = y1;


		Columns[1].x = x2;
		Columns[1].y = y2;

	};
	constexpr Matrix2X2(Vector2 _vec, Vector2 _vec2) {

		Columns[0] = _vec;
		Columns[1] = _vec2;
	};
	constexpr Matrix2X2() = default;
	

	
	constexpr inline static Matrix2X2 Identity()
	{
		return Matrix2X2(1, 0, 0, 1);
	};


	constexpr inline Vector2& operator[](const int& i)
	{
		return Columns[i];
	}
	constexpr inline const Vector2& operator[](const int& i) const
	{
		return Columns[i];
	}

	explicit operator Matrix() const;
	explicit operator Matrix3X3() const;
	explicit operator Matrix4X4() const;


private:

};


inline Matrix2X2 operator+(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator-(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator*(const Matrix2X2& matrix1, const Matrix2X2& matrix2);
inline Matrix2X2 operator*(float value, const Matrix2X2& matrix1);

inline Matrix2X2 operator-(const Matrix2X2& matrix2);


// Operator booleans // 

constexpr inline bool operator==(const Matrix2X2& matrix1 ,const Matrix2X2& matrix2)
{
	const float* ptr1 = matrix1.GetPtr();
	const float* ptr2 = matrix2.GetPtr();
	constexpr const int size = Matrix2X2::Size();
	
	for (size_t i = 0; i < size; i++)
	{
		if (ptr1[i] != ptr2[i])
			return false;
	}

	return true;
}

constexpr inline bool operator!=(const Matrix2X2& matrix1, const Matrix2X2& matrix2)
{
	const float* ptr1 = matrix1.GetPtr();
	const float* ptr2 = matrix2.GetPtr();
	constexpr const int size = Matrix2X2::Size();

	for (size_t i = 0; i < size; i++)
	{
		if (ptr1[i] != ptr2[i])
			return true;
	}

	return false;
}






std::ostream& operator<<(std::ostream& stream,const Matrix2X2& matrix);