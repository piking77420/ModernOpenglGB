#include "Matrix3X3.h"
#include "Vector2.h"
#include "Matrix.h"
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

	result.Coloms[0].x = cos((angle));
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = sin((angle));
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;

	return result;

}



Matrix3X3 Matrix3X3::Identity() const
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

Matrix3X3 Matrix3X3::operator*(const Matrix3X3& matrix)
{
	Matrix3X3 result;



	result.Coloms[0].x = this->Coloms[0].x * matrix[0].x + this->Coloms[0].y * matrix[1].x + this->Coloms[0].z * matrix[2].x;
	result.Coloms[0].y = this->Coloms[0].x * matrix[0].y + this->Coloms[0].y * matrix[1].y + this->Coloms[0].z * matrix[2].y ;
	result.Coloms[0].z = this->Coloms[0].x * matrix[0].z + this->Coloms[0].y * matrix[1].z + this->Coloms[0].z * matrix[2].z ;

	result.Coloms[1].x = this->Coloms[1].x * matrix[0].x + this->Coloms[1].y * matrix[1].x + this->Coloms[1].z * matrix[2].x ;
	result.Coloms[1].y = this->Coloms[1].x * matrix[0].y + this->Coloms[1].y * matrix[1].y + this->Coloms[1].z * matrix[2].y ;
	result.Coloms[1].z = this->Coloms[1].x * matrix[0].z + this->Coloms[1].y * matrix[1].z + this->Coloms[1].z * matrix[2].z ;

	result.Coloms[2].x = this->Coloms[2].x * matrix[0].x + this->Coloms[2].y * matrix[1].x + this->Coloms[2].z * matrix[2].x ;
	result.Coloms[2].y = this->Coloms[2].x * matrix[0].y + this->Coloms[2].y * matrix[1].y + this->Coloms[2].z * matrix[2].y ;
	result.Coloms[2].z = this->Coloms[2].x * matrix[0].z + this->Coloms[2].y * matrix[1].z + this->Coloms[2].z * matrix[2].z ;


	return result;
}

Matrix3X3 Matrix3X3::Invert()
{
	Matrix m = (Matrix)*this;

	m = m.Invert();

	return (Matrix3X3)m;
}

Matrix3X3 Matrix3X3::Transposate() const
{
	Matrix3X3 result;

	
	for (size_t x = 0; x < 3; x++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			result[x][y] = Coloms[y][x];
		}
	}


	return result;
}

Vector3& Matrix3X3::operator[](const int& i)
{
	return Coloms[i];
}

const Vector3&  Matrix3X3::operator[](const int& i) const
{
	return Coloms[i];
}





Matrix3X3::operator Matrix()
{
	Matrix result = Matrix(3); 

	result[0][0] = Coloms[0].x;
	result[1][0] = Coloms[0].y;
	result[2][0] = Coloms[0].z;

	result[0][1] = Coloms[1].x;
	result[1][1] = Coloms[1].y;
	result[2][1] = Coloms[1].z;


	result[0][2] = Coloms[2].x;
	result[1][2] = Coloms[2].y;
	result[2][2] = Coloms[2].z;

	return result;
}

const float* Matrix3X3::GetPtr() const
{
	return &Coloms[0].x;
}

float* Matrix3X3::SetPtr()
{
	return &Coloms[0].x;
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

	result.Coloms[0] = max.Coloms[0] + (Vector3)max1.Coloms[0];
	result.Coloms[1] = max.Coloms[1] + (Vector3)max1.Coloms[1];
	result.Coloms[2] = max.Coloms[2];

	return result;
}

 Matrix3X3 operator+(const Matrix2X2& max, const Matrix3X3& max1)
{
	Matrix3X3 result;

	result.Coloms[0] = (Vector3)max.Coloms[0] + max1.Coloms[0];
	result.Coloms[1] = (Vector3)max.Coloms[1] + max1.Coloms[1];
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


	result.Coloms[0] = (Vector3)max.Coloms[0] + max1.Coloms[0];
	result.Coloms[1] = (Vector3)max.Coloms[1] + max1.Coloms[1];
	result.Coloms[2] = max1.Coloms[2];

	return Matrix3X3();
}


 Matrix3X3 operator-(const Matrix3X3& max, const Matrix2X2& max1)
{
	Matrix3X3 result;

	result.Coloms[0] = max.Coloms[0] - (Vector3)max1.Coloms[0];
	result.Coloms[1] = max.Coloms[1] - (Vector3)max1.Coloms[1];
	result.Coloms[2] = max.Coloms[2];

	return result;
}

 Matrix3X3 operator*(const float& value, const Matrix2X2& max)
{
	return Matrix3X3();
}

 std::ostream& operator<<(std::ostream& stream, const Matrix3X3& maxtrix)
 {
	 stream << maxtrix.Coloms[0].x << " " << maxtrix.Coloms[1].x << " " << maxtrix.Coloms[2].x << " ";
	 stream << '\n';
	 stream << maxtrix.Coloms[0].y << " " << maxtrix.Coloms[1].y << " " << maxtrix.Coloms[2].y << " ";
	 stream << '\n';
	 stream << maxtrix.Coloms[0].z << " " << maxtrix.Coloms[1].z << " " << maxtrix.Coloms[2].z << " ";
	

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
