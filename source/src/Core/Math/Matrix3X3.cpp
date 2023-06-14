#include "Matrix3X3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Mathf.h"






Matrix3X3 Matrix3X3::TranslationMatrix3X3(const Vector2& translation)
{
	Matrix3X3 result;

	result.Ligns[0].x = translation.x;
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;


	result.Ligns[1].x = 0;
	result.Ligns[1].y = translation.y;
	result.Ligns[1].z = 0;



	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = 1;


	return result;
}

Matrix3X3 Matrix3X3::Rotation2DMatrix3X3(const float& angle)
{
	Matrix3X3 result;

	result.Ligns[0].x = cos(degreesToRadians(angle));
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;


	result.Ligns[1].x = 0;
	result.Ligns[1].y = sin(degreesToRadians(angle));
	result.Ligns[1].z = 0;



	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = 1;

	return result;

}



Matrix3X3 Matrix3X3::Identity()
{
	Matrix3X3 result;

	result.Ligns[0].x = 1;
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;


	result.Ligns[1].x = 0;
	result.Ligns[1].y = 1;
	result.Ligns[1].z = 0;



	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = 1;


	return result;
}

Matrix3X3::Matrix3X3(const Vector3& a, const Vector3& b, const Vector3& c)
{
	Ligns[0] = a;
	Ligns[1] = b;
	Ligns[2] = c;
	

}

Matrix3X3 Matrix3X3::operator*(const Matrix3X3& matrix)
{
	Matrix3X3 result;






	result.Ligns[0].x = this->Ligns[0].x * matrix[0].x + this->Ligns[0].y * matrix[1].x + this->Ligns[0].z * matrix[2].x;
	result.Ligns[0].y = this->Ligns[0].x * matrix[0].y + this->Ligns[0].y * matrix[1].y + this->Ligns[0].z * matrix[2].y ;
	result.Ligns[0].z = this->Ligns[0].x * matrix[0].z + this->Ligns[0].y * matrix[1].z + this->Ligns[0].z * matrix[2].z ;

	result.Ligns[1].x = this->Ligns[1].x * matrix[0].x + this->Ligns[1].y * matrix[1].x + this->Ligns[1].z * matrix[2].x ;
	result.Ligns[1].y = this->Ligns[1].x * matrix[0].y + this->Ligns[1].y * matrix[1].y + this->Ligns[1].z * matrix[2].y ;
	result.Ligns[1].z = this->Ligns[1].x * matrix[0].z + this->Ligns[1].y * matrix[1].z + this->Ligns[1].z * matrix[2].z ;

	result.Ligns[2].x = this->Ligns[2].x * matrix[0].x + this->Ligns[2].y * matrix[1].x + this->Ligns[2].z * matrix[2].x ;
	result.Ligns[2].y = this->Ligns[2].x * matrix[0].y + this->Ligns[2].y * matrix[1].y + this->Ligns[2].z * matrix[2].y ;
	result.Ligns[2].z = this->Ligns[2].x * matrix[0].z + this->Ligns[2].y * matrix[1].z + this->Ligns[2].z * matrix[2].z ;

	




	return result;
}

Vector3 Matrix3X3::operator[](const int& i) const
{
	return Ligns[i];
}





Matrix3X3::operator Matrix()
{
	Matrix result = Matrix(3); 

	result[0][0] = Ligns[0].x;
	result[0][1] = Ligns[0].y;
	result[0][2] = Ligns[0].z;

	result[1][0] = Ligns[1].x;
	result[1][1] = Ligns[1].y;
	result[1][2] = Ligns[1].z;


	result[2][1] = Ligns[2].x;
	result[2][2] = Ligns[2].z;
	result[2][3] = Ligns[2].y;

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

	result.Ligns[0] = max.Ligns[0] + (Vector3)max1.Ligns[0];
	result.Ligns[1] = max.Ligns[1] + (Vector3)max1.Ligns[1];
	result.Ligns[2] = max.Ligns[2];

	return result;
}

 Matrix3X3 operator+(const Matrix2X2& max, const Matrix3X3& max1)
{
	Matrix3X3 result;

	result.Ligns[0] = (Vector3)max.Ligns[0] + max1.Ligns[0];
	result.Ligns[1] = (Vector3)max.Ligns[1] + max1.Ligns[1];
	result.Ligns[2] = max1.Ligns[2];

	return result;
}


 Matrix3X3 operator+(const Matrix3X3& max, const Matrix3X3& max1)
{
	Matrix3X3 result;


	result.Ligns[0] = max.Ligns[0] + max1.Ligns[0];
	result.Ligns[1] = max.Ligns[1] + max1.Ligns[1];
	result.Ligns[2] = max.Ligns[2] + max1.Ligns[2];


	return result;
}

 Matrix3X3 operator-(const Matrix3X3& max, const Matrix3X3& max1)
{
	Matrix3X3 result;


	result.Ligns[0] = max.Ligns[0] - max1.Ligns[0];
	result.Ligns[1] = max.Ligns[1] - max1.Ligns[1];
	result.Ligns[2] = max.Ligns[2] - max1.Ligns[2];


	return result;
}



 Matrix3X3 operator-(const Matrix2X2& max, const Matrix3X3& max1)
{
	Matrix3X3 result;


	result.Ligns[0] = (Vector3)max.Ligns[0] + max1.Ligns[0];
	result.Ligns[1] = (Vector3)max.Ligns[1] + max1.Ligns[1];
	result.Ligns[2] = max1.Ligns[2];

	return Matrix3X3();
}


 Matrix3X3 operator-(const Matrix3X3& max, const Matrix2X2& max1)
{
	Matrix3X3 result;

	result.Ligns[0] = max.Ligns[0] - (Vector3)max1.Ligns[0];
	result.Ligns[1] = max.Ligns[1] - (Vector3)max1.Ligns[1];
	result.Ligns[2] = max.Ligns[2];

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
		 stream << maxtrix.Ligns[i].x << " " << maxtrix.Ligns[i].y << " " << maxtrix.Ligns[i].z << " ";
		 stream << '\n';
	 }

	 return stream;
 }



 Matrix3X3 operator*(const float& value, const Matrix3X3& max)
{
	Matrix3X3 result = max;

	result.Ligns[0].x *= value;
	result.Ligns[0].y *= value;
	result.Ligns[0].z *= value;


	result.Ligns[1].x *= value;
	result.Ligns[1].y *= value;
	result.Ligns[1].z *= value;

	result.Ligns[2].x *= value;
	result.Ligns[2].y *= value;
	result.Ligns[2].z *= value;



	return result;


}
