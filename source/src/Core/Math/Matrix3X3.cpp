#include "Matrix3X3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Mathf.h"






Matrix3X3 Matrix3X3::TranslationMatrix3X3(const Vector2& translation)
{
	Matrix3X3 result;

	result.Coloms[0].x = translation.x;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = translation.y;
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;


	return result;
}

Matrix3X3 Matrix3X3::Rotation2DMatrix3X3(const float& angle)
{
	Matrix3X3 result;

	result.Coloms[0].x = cos(degreesToRadians(angle));
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = sin(degreesToRadians(angle));
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;

	return result;

}



Matrix3X3 Matrix3X3::Identity()
{
	Matrix3X3 result;

	result.Coloms[0].x = 1;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = 1;
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;


	return result;
}

Matrix3X3::Matrix3X3(const Vector3& a, const Vector3& b, const Vector3& c)
{
	Coloms[0] = a;
	Coloms[1] = b;
	Coloms[2] = c;
	

}

Matrix3X3::operator Matrix()
{
	Matrix result = Matrix(3); 

	result[0][0] = Coloms[0].x;
	result[0][1] = Coloms[0].y;
	result[0][2] = Coloms[0].z;

	result[1][0] = Coloms[1].x;
	result[1][1] = Coloms[1].y;
	result[1][2] = Coloms[1].z;


	result[2][1] = Coloms[2].x;
	result[2][2] = Coloms[2].z;
	result[2][3] = Coloms[2].y;

	return result;
}



Matrix3X3::Matrix3X3()
{
}

Matrix3X3::~Matrix3X3()
{
}

 Matrix3X3 operator+(const Matrix3X3& max, const Matrix2X2& max1)
{
	Matrix3X3 result;

	result.Coloms[0] = max.Coloms[0] + (Vector3)max1.Rows[0];
	result.Coloms[1] = max.Coloms[1] + (Vector3)max1.Rows[1];
	result.Coloms[2] = max.Coloms[2];

	return result;
}

 Matrix3X3 operator+(const Matrix2X2& max, const Matrix3X3& max1)
{
	Matrix3X3 result;

	result.Coloms[0] = (Vector3)max.Rows[0] + max1.Coloms[0];
	result.Coloms[1] = (Vector3)max.Rows[1] + max1.Coloms[1];
	result.Coloms[2] = max1.Coloms[2];

	return result;
}


 Matrix3X3 operator+(const Matrix3X3& max, const Matrix3X3& max1)
{
	Matrix3X3 result;


	result.Coloms[0] = max.Coloms[0] + max1.Coloms[0];
	result.Coloms[1] = max.Coloms[1] + max1.Coloms[1];
	result.Coloms[2] = max.Coloms[2] + max1.Coloms[2];


	return result;
}

 Matrix3X3 operator-(const Matrix3X3& max, const Matrix3X3& max1)
{
	Matrix3X3 result;


	result.Coloms[0] = max.Coloms[0] - max1.Coloms[0];
	result.Coloms[1] = max.Coloms[1] - max1.Coloms[1];
	result.Coloms[2] = max.Coloms[2] - max1.Coloms[2];


	return result;
}



 Matrix3X3 operator-(const Matrix2X2& max, const Matrix3X3& max1)
{
	Matrix3X3 result;


	result.Coloms[0] = (Vector3)max.Rows[0] + max1.Coloms[0];
	result.Coloms[1] = (Vector3)max.Rows[1] + max1.Coloms[1];
	result.Coloms[2] = max1.Coloms[2];

	return Matrix3X3();
}


 Matrix3X3 operator-(const Matrix3X3& max, const Matrix2X2& max1)
{
	Matrix3X3 result;

	result.Coloms[0] = max.Coloms[0] - (Vector3)max1.Rows[0];
	result.Coloms[1] = max.Coloms[1] - (Vector3)max1.Rows[1];
	result.Coloms[2] = max.Coloms[2];

	return result;
}

 Matrix3X3 operator*(const float& value, const Matrix2X2& max)
{
	return Matrix3X3();
}

 std::ostream& operator<<(std::ostream& stream, const Matrix3X3& maxtrix)
 {
	 for (size_t i = 0; i < 3; i++)
	 {
		 stream << maxtrix.Coloms[i].x << " ";
	 }
	 stream << '\n';
	 for (size_t i = 0; i < 3; i++)
	 {
		 stream << maxtrix.Coloms[i].y << " ";
	 }
	 stream << '\n';

	 for (size_t i = 0; i < 3; i++)
	 {
		 stream << maxtrix.Coloms[i].z << " ";
	 }
	 stream << '\n';
	 return stream;
 }



 Matrix3X3 operator*(const float& value, const Matrix3X3& max)
{
	Matrix3X3 result = max;

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
