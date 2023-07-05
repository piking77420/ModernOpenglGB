#include "Matrix4X4.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Mathf.h"










// fov int degres  , aspect widh/height , near 0.1 , far 1000.f
Matrix4X4 Matrix4X4::ProjectionMatrix(const float& fov, const float& aspect, const float& Near, const float& Far)
{
	Matrix4X4 result;



	float fFovRad = 1.0f / std::tan((fov / 180.f * 3.14159f) * 0.5f);

	float zdiff = Near - Far;


	result.Columns[0].x = fFovRad / aspect;
	result.Columns[0].y = 0;
	result.Columns[0].z = 0;
	result.Columns[0].w = 0;

	result.Columns[1].x = 0;
	result.Columns[1].y = fFovRad;
	result.Columns[1].z = 0;
	result.Columns[1].w = 0;

	result.Columns[2].x = 0;
	result.Columns[2].y = 0;
	result.Columns[2].z = (Far + Near) / zdiff;
	result.Columns[2].w = -1.0f;

	result.Columns[3].x = 0;
	result.Columns[3].y = 0;
	result.Columns[3].z = (2 * Far * Near) / zdiff;
	result.Columns[3].w = 0;

	return result;


}
// SUS
Matrix4X4 Matrix4X4::OrthoGraphicMatrix(float top, float bot, float right, float left, float Near, float Far)
{
	Matrix4X4 result;

	float topBottomDiff = top - bot;
	float rightLeftDiff = right - left;
	float farMinusNear = Far - Near;

	float r00 = 2.0f / rightLeftDiff;
	float r11 = 2.0f / topBottomDiff;
	float r22 = -2.0f / farMinusNear;

	float r03 = -(right + left) / rightLeftDiff;
	float r13 = -(top + bot) / topBottomDiff;
	float r23 = -(Far + Near) / farMinusNear;



	result[0] = Vector4(r00, 0, 0, r03);
	result[1] = Vector4(0, r11, 0, r13);
	result[2] = Vector4(0, 0, r22, r23);
	result[3] = Vector4(0, 0, 0, 1.f);

	return result;

}





Vector3 Matrix4X4::GetPos()
{
	return Vector3(Columns[3]);
}

Matrix4X4 Matrix4X4::ScalingMatrix4X4(const Vector3& ScalingFactor)
{
	Matrix4X4 result;
	
	result.Columns[0].x = ScalingFactor.x;
	result.Columns[0].y = 0;
	result.Columns[0].z = 0;
	result.Columns[0].w = 0;

	result.Columns[1].x = 0;
	result.Columns[1].y = ScalingFactor.y;
	result.Columns[1].z = 0;
	result.Columns[1].w = 0;

	result.Columns[2].x = 0;
	result.Columns[2].y = 0;
	result.Columns[2].z = ScalingFactor.z;
	result.Columns[2].w = 0;

	result.Columns[3].x = 0;
	result.Columns[3].y = 0;
	result.Columns[3].z = 0;
	result.Columns[3].w = 1;
	
	return result;
}

Matrix4X4 Matrix4X4::RotationX4X4(const float& angle)
{
	Matrix4X4 result;
	
	result.Columns[0].x = 1;
	result.Columns[0].y = 0;
	result.Columns[0].z = 0;
	result.Columns[0].w = 0;

	result.Columns[1].x = 0;
	result.Columns[1].y = cos((angle));
	result.Columns[1].z = -sin((angle));
	result.Columns[1].w = 0;

	result.Columns[2].x = 0;
	result.Columns[2].y = sin((angle));
	result.Columns[2].z = cos((angle));
	result.Columns[2].w = 0;

	result.Columns[3].x = 0;
	result.Columns[3].y = 0;
	result.Columns[3].z = 0;
	result.Columns[3].w = 1;
	

	return result;

}

Matrix4X4 Matrix4X4::RotationMatrix4X4(const Vector3& angle)
{
	Matrix4X4 result;


	result = RotationZ4X4(angle.z) * RotationY4X4(angle.y) * RotationX4X4(angle.x);




	return result;
}

Matrix4X4 Matrix4X4::TranslateMatrix4X4(const Vector3& translation)
{
	Matrix4X4 result;
	
	result = result.Identity();

	result[3].x = translation.x;
	result[3].y = translation.y;
	result[3].z = translation.z;
	result[3].w = 1;

		
	return result;
}

Matrix4X4 Matrix4X4::TRS(const Vector3& translation, const Vector3& angle, const Vector3& scaling)
{
	Matrix4X4 translationMatrix = TranslateMatrix4X4(translation);
	Matrix4X4 rotationMatrix = RotationMatrix4X4(angle);
	Matrix4X4 scalingMatrix = ScalingMatrix4X4(scaling);
	return (  translationMatrix * ( rotationMatrix * scalingMatrix));
}


// rad
Matrix4X4 Matrix4X4::RotationY4X4(const float& angle)
{
	Matrix4X4 result;
	
	
	result.Columns[0].x = cos((angle));
	result.Columns[0].y = 0;
	result.Columns[0].z = sin((angle));
	result.Columns[0].w = 0;

	result.Columns[1].x = 0;
	result.Columns[1].y = 1;
	result.Columns[1].z = 0;
	result.Columns[1].w = 0;

	result.Columns[2].x = -sin((angle));
	result.Columns[2].y = 0;
	result.Columns[2].z = cos((angle));
	result.Columns[2].w = 0;

	result.Columns[3].x = 0;
	result.Columns[3].y = 0;
	result.Columns[3].z = 0;
	result.Columns[3].w = 1;
	
	return result;
}

// rad
Matrix4X4 Matrix4X4::RotationZ4X4(const float& angle)
{
	Matrix4X4 result;
	



	result.Columns[0].x = cos((angle));
	result.Columns[0].y = -sin((angle));
	result.Columns[0].z = 0;
	result.Columns[0].w = 0;

	result.Columns[1].x = sin((angle));
	result.Columns[1].y = cos((angle));
	result.Columns[1].z = 0;
	result.Columns[1].w = 0;

	result.Columns[2].x = 0;
	result.Columns[2].y = 0;
	result.Columns[2].z = 1;
	result.Columns[2].w = 0;

	result.Columns[3].x = 0;
	result.Columns[3].y = 0;
	result.Columns[3].z = 0;
	result.Columns[3].w = 1;
	
	return result;
}

 Matrix4X4 Matrix4X4::operator*(const Matrix4X4& matrix) const
{

	 Matrix4X4 result;

	 result.Columns[0].x = this->Columns[0].x * matrix[0].x + this->Columns[1].x * matrix[0].y + this->Columns[2].x * matrix[0].z + this->Columns[3].x * matrix[0].w;
	 result.Columns[0].y = this->Columns[0].y * matrix[0].x + this->Columns[1].y * matrix[0].y + this->Columns[2].y * matrix[0].z + this->Columns[3].y * matrix[0].w;
	 result.Columns[0].z = this->Columns[0].z * matrix[0].x + this->Columns[1].z * matrix[0].y + this->Columns[2].z * matrix[0].z + this->Columns[3].z * matrix[0].w;
	 result.Columns[0].w = this->Columns[0].w * matrix[0].x + this->Columns[1].w * matrix[0].y + this->Columns[2].w * matrix[0].z + this->Columns[3].w * matrix[0].w;

	 result.Columns[1].x = this->Columns[0].x * matrix[1].x + this->Columns[1].x * matrix[1].y + this->Columns[2].x * matrix[1].z + this->Columns[3].x * matrix[1].w;
	 result.Columns[1].y = this->Columns[0].y * matrix[1].x + this->Columns[1].y * matrix[1].y + this->Columns[2].y * matrix[1].z + this->Columns[3].y * matrix[1].w;
	 result.Columns[1].z = this->Columns[0].z * matrix[1].x + this->Columns[1].z * matrix[1].y + this->Columns[2].z * matrix[1].z + this->Columns[3].z * matrix[1].w;
	 result.Columns[1].w = this->Columns[0].w * matrix[1].x + this->Columns[1].w * matrix[1].y + this->Columns[2].w * matrix[1].z + this->Columns[3].w * matrix[1].w;

	 result.Columns[2].x = this->Columns[0].x * matrix[2].x + this->Columns[1].x * matrix[2].y + this->Columns[2].x * matrix[2].z + this->Columns[3].x * matrix[2].w;
	 result.Columns[2].y = this->Columns[0].y * matrix[2].x + this->Columns[1].y * matrix[2].y + this->Columns[2].y * matrix[2].z + this->Columns[3].y * matrix[2].w;
	 result.Columns[2].z = this->Columns[0].z * matrix[2].x + this->Columns[1].z * matrix[2].y + this->Columns[2].z * matrix[2].z + this->Columns[3].z * matrix[2].w;
	 result.Columns[2].w = this->Columns[0].w * matrix[2].x + this->Columns[1].w * matrix[2].y + this->Columns[2].w * matrix[2].z + this->Columns[3].w * matrix[2].w;

	 result.Columns[3].x = this->Columns[0].x * matrix[3].x + this->Columns[1].x * matrix[3].y + this->Columns[2].x * matrix[3].z + this->Columns[3].x * matrix[3].w;
	 result.Columns[3].y = this->Columns[0].y * matrix[3].x + this->Columns[1].y * matrix[3].y + this->Columns[2].y * matrix[3].z + this->Columns[3].y * matrix[3].w;
	 result.Columns[3].z = this->Columns[0].z * matrix[3].x + this->Columns[1].z * matrix[3].y + this->Columns[2].z * matrix[3].z + this->Columns[3].z * matrix[3].w;
	 result.Columns[3].w = this->Columns[0].w * matrix[3].x + this->Columns[1].w * matrix[3].y + this->Columns[2].w * matrix[3].z + this->Columns[3].w * matrix[3].w;

	 return result;

	
}


Vector4 ReturnLign(const Matrix4X4& matrix ,int index) 
{
	Vector4 vec;

	if(index == 0)
	{
		vec = Vector4(matrix.Columns[0].x, matrix.Columns[1].x, matrix.Columns[2].x, matrix.Columns[3].x);
	}
	else if(index == 1)
	{
		vec = Vector4(matrix.Columns[0].y, matrix.Columns[1].y, matrix.Columns[2].y, matrix.Columns[3].y);
	}else if(index == 2)
	{
		vec = Vector4(matrix.Columns[0].z, matrix.Columns[1].z, matrix.Columns[2].z, matrix.Columns[3].z);
	}
	else if (index == 3)
	{
		vec = Vector4(matrix.Columns[0].w, matrix.Columns[1].w, matrix.Columns[2].w, matrix.Columns[3].w);
	}
	else
	{
		return vec;
	}

	return vec;
}

Matrix4X4 Matrix4X4::Invert() const 
{
	Matrix4X4 matrix = *this;
	Matrix m = Matrix(matrix).ReturnInv();
	Matrix4X4 matrixRerturn = (Matrix4X4)m;

	return matrixRerturn;
}

Matrix4X4 Matrix4X4::Identity()
{
	Matrix4X4 result;

	result.Columns[0].x = 1;
	result.Columns[0].y = 0;
	result.Columns[0].z = 0;
	result.Columns[0].w = 0;

	result.Columns[1].x = 0;
	result.Columns[1].y = 1;
	result.Columns[1].z = 0;
	result.Columns[1].w = 0;

	result.Columns[2].x = 0;
	result.Columns[2].y = 0;
	result.Columns[2].z = 1;
	result.Columns[2].w = 0;

	result.Columns[3].x = 0;
	result.Columns[3].y = 0;
	result.Columns[3].z = 0;
	result.Columns[3].w = 1;


	return result;
}

Matrix4X4 Matrix4X4::Transposate() const
{
	Matrix4X4 result;

	result[0].x = Columns[0].x ; result[0].y = Columns[1].x ; result[0].z = Columns[2].x ; result[0].w = Columns[3].x ;
	result[1].x = Columns[0].y ; result[1].y = Columns[1].y ; result[1].z = Columns[2].y ; result[1].w = Columns[3].y ;
	result[2].x = Columns[0].z ; result[2].y = Columns[1].z ; result[2].z = Columns[2].z ; result[2].w = Columns[3].z ;
	result[3].x = Columns[0].w ; result[3].y = Columns[1].w ; result[3].z = Columns[2].w ; result[3].w = Columns[3].w ;






	return result;
}

float Matrix4X4::Determinant() const
{
	Matrix4X4 matrix = *this;
	float result = Matrix::CalculateDertimant(Matrix(matrix));
	return result;
}

Vector4 Matrix4X4::operator[](const int& i) const
{
	return Columns[i];
}

Vector4& Matrix4X4::operator[](const int& i)
{
	return Columns[i];
}

Matrix4X4 Matrix4X4::LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 zaxis = (at - eye).Normalize();
	Vector3 xaxis = (up.CrossProduct(zaxis)).Normalize();
	Vector3 yaxis = zaxis.CrossProduct(xaxis);

	zaxis = -zaxis;

	Matrix4X4 LookAtMatrix;

	LookAtMatrix.Columns[0].x = xaxis.x;
	LookAtMatrix.Columns[0].y = yaxis.x;
	LookAtMatrix.Columns[0].z = zaxis.x;
	LookAtMatrix.Columns[0].w = 0;

	LookAtMatrix.Columns[1].x = xaxis.y;
	LookAtMatrix.Columns[1].y = yaxis.y;
	LookAtMatrix.Columns[1].z = zaxis.y;
	LookAtMatrix.Columns[1].w = 0;

	LookAtMatrix.Columns[2].x = xaxis.z;
	LookAtMatrix.Columns[2].y = yaxis.z;
	LookAtMatrix.Columns[2].z = zaxis.z;
	LookAtMatrix.Columns[2].w = 0;

	LookAtMatrix.Columns[3].x = -(xaxis.DotProduct(eye));
	LookAtMatrix.Columns[3].y = -(yaxis.DotProduct(eye));
	LookAtMatrix.Columns[3].z = -(zaxis.DotProduct(eye));
	LookAtMatrix.Columns[3].w = 1;


	return LookAtMatrix;


}



const float* Matrix4X4::GetPtr() const
{
	return &Columns[0].x;
}

float* Matrix4X4::SetPtr()
{
	return &Columns[0].x;
}

Matrix4X4::Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
{
	Columns[0] = a;
	Columns[1] = b;
	Columns[2] = c;
	Columns[3] = d;
}

Matrix4X4 Rotate(const Matrix4X4& matrix, const Vector3& angle)
{
	return  Matrix4X4().Identity() *  (Matrix4X4().RotationMatrix4X4(angle) * matrix);

}

Matrix4X4 Translate(const Matrix4X4& matrix, const Vector3& angle)
{
	Matrix4X4 result = matrix;
	result.Columns[3] += angle;


	return result;
}

Matrix4X4::operator Matrix()
{
	Matrix result = Matrix(4);

	result[0][0] = Columns[0].x;
	result[0][1] = Columns[0].y;
	result[0][2] = Columns[0].z;
	result[0][3] = Columns[0].w;


	result[1][0] = Columns[1].x;
	result[1][1] = Columns[1].y;
	result[1][2] = Columns[1].z;
	result[1][3] = Columns[1].w;


	result[2][0] = Columns[2].x;
	result[2][1] = Columns[2].z;
	result[2][2] = Columns[2].y;
	result[2][3] = Columns[2].w;


	result[3][0] = Columns[3].x;
	result[3][1] = Columns[3].z;
	result[3][2] = Columns[3].y;
	result[3][3] = Columns[3].w;

	return result;
}



Matrix4X4::Matrix4X4()
{
	for (size_t i = 0; i < 4; i++)
	{
		Columns[i].x = 0;
		Columns[i].y = 0;
		Columns[i].z = 0;
		Columns[i].w = 0;

	}
}

Matrix4X4::~Matrix4X4()
{
}

 Vector4 operator*( Matrix4X4& matrix, const Vector4& Row1)
{
		

	 Vector4 newVec;



	 newVec.x = (Row1.x * matrix[0].x) + (Row1.y * matrix[0].y) + (Row1.z * matrix[0].z) + (Row1.w * matrix[0].w);

	 newVec.y = (Row1.x * matrix[1].x) + (Row1.y * matrix[1].y) + (Row1.z * matrix[1].z) + (Row1.w * matrix[1].w);

	 newVec.z = (Row1.x * matrix[2].x) + (Row1.y * matrix[2].y) + (Row1.z * matrix[2].z) + (Row1.w * matrix[2].w);

	 newVec.w = (Row1.x * matrix[3].x) + (Row1.y * matrix[3].y) + (Row1.z * matrix[3].z) + (Row1.w * matrix[3].w);



	 return newVec;
	
}

 Vector4 operator*(const Vector4& Row1, const Matrix4X4& matrix)
 {




		 Vector4 newVec;



		 newVec.x = (Row1.x * matrix[0].x) + (Row1.y * matrix[0].y)  +( Row1.z * matrix[0].z)  +( Row1.w * matrix[0].w);

		 newVec.y = (Row1.x * matrix[1].x) + (Row1.y * matrix[1].y)  +(Row1.z * matrix[1].z)  +(Row1.w * matrix[1].w);

		 newVec.z = (Row1.x * matrix[2].x) + (Row1.y * matrix[2].y)  +(Row1.z * matrix[2].z)  +(Row1.w * matrix[2].w);

		 newVec.w = (Row1.x * matrix[3].x) + (Row1.y * matrix[3].y)  +(Row1.z * matrix[3].z)  +(Row1.w * matrix[3].w);



		 return newVec;
 }
 
std::ostream& operator<<(std::ostream& stream, const Matrix4X4& maxtrix)
{
	
	stream << maxtrix.Columns[0].x << " " << maxtrix.Columns[1].x << " " << maxtrix.Columns[2].x << " " << maxtrix.Columns[3].x << " ";
	stream << '\n';
	stream << maxtrix.Columns[0].y << " " << maxtrix.Columns[1].y << " " << maxtrix.Columns[2].y << " " << maxtrix.Columns[3].y << " ";
	stream << '\n';
	stream << maxtrix.Columns[0].z << " " << maxtrix.Columns[1].z << " " << maxtrix.Columns[2].z << " " << maxtrix.Columns[3].z << " ";
	stream << '\n';
	stream << maxtrix.Columns[0].w << " " << maxtrix.Columns[1].w << " " << maxtrix.Columns[2].w << " " << maxtrix.Columns[3].w << " ";


	



	return stream;
}