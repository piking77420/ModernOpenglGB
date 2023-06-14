#include "Matrix4X4.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Mathf.h"









Matrix4X4 Matrix4X4::ViewMatrix(const Vector3& Left, const Vector3& Up, const Vector3& Forward, const Vector3& Translation)
{
	Matrix4X4 result;

	result.Ligns[0].x = Left.x;
	result.Ligns[1].x = Left.y;
	result.Ligns[2].x = Left.z;
	result.Ligns[3].x = 0;

	result.Ligns[0].y = Up.x;
	result.Ligns[1].y = Up.y;
	result.Ligns[2].y = Up.z;
	result.Ligns[3].y = 0;

	result.Ligns[0].z = Forward.x;
	result.Ligns[1].z = Forward.y;
	result.Ligns[2].z = Forward.z;
	result.Ligns[3].z = 0;

	result.Ligns[3].w = Translation.x;
	result.Ligns[3].w = Translation.y;
	result.Ligns[3].w = Translation.z;
	result.Ligns[3].w = 1;

	return result;
}

// fov int degres  , aspect widh/height , near 0.1 , far 1000.f
Matrix4X4 Matrix4X4::ProjectionMatrix(const float& fov, const float& aspect, const float& Near, const float& Far)
{
	Matrix4X4 result;



	float fFovRad = 1.0f / std::tan((fov / 180.f * 3.14159f) * 0.5f);

	float zdiff = Far - Near;


	result.Ligns[0].x = fFovRad / aspect;
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;
	result.Ligns[0].w = 0;

	result.Ligns[1].x = 0;
	result.Ligns[1].y = fFovRad;
	result.Ligns[1].z = 0;
	result.Ligns[1].w = 0;

	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = (Far + Near) / zdiff;
	result.Ligns[2].w = -(2 * Far * Near) / zdiff;

	result.Ligns[3].x = 0;
	result.Ligns[3].y = 0 ;
	result.Ligns[3].z = -1.0f;
	result.Ligns[3].w = 0;

	return result;

}

Matrix4X4 Matrix4X4::OrthoGraphicMatrix(float top, float bot, float right, float left, float Near, float Far)
{

	Matrix4X4 result;

	float topbottomDiff = top - bot;
	float rightLeftDiff = left - right;

	result.Ligns[0].x = 2.f  / right - left ;
	result.Ligns[1].x = 0;
	result.Ligns[2].x = 0;
	result.Ligns[3].x = 0;

	result.Ligns[0].y = 0;
	result.Ligns[1].y =  2.f / (top - bot) ;
	result.Ligns[2].y = 0;
	result.Ligns[3].y = 0;

	result.Ligns[0].z = 0;
	result.Ligns[1].z = 0;
	result.Ligns[2].z = 1.f / (Far - Near  );
	result.Ligns[3].z = 0;

	result.Ligns[0].w = (left + right )/ (left - right);
	result.Ligns[1].w = -(top + bot )/ (bot - top);
	result.Ligns[2].w = (Near) / (Near - Far);
	result.Ligns[3].w = 1.f;


	return result;
}




Vector3 Matrix4X4::GetPos()
{
	return Vector3(Ligns[3]);
}

Matrix4X4 Matrix4X4::ScalingMatrix4X4(const Vector3& ScalingFactor)
{
	Matrix4X4 result;
	
	result.Ligns[0].x = ScalingFactor.x;
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;
	result.Ligns[0].w = 0;

	result.Ligns[1].x = 0;
	result.Ligns[1].y = ScalingFactor.y;
	result.Ligns[1].z = 0;
	result.Ligns[1].w = 0;

	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = ScalingFactor.z;
	result.Ligns[2].w = 0;

	result.Ligns[3].x = 0;
	result.Ligns[3].y = 0;
	result.Ligns[3].z = 0;
	result.Ligns[3].w = 1;
	
	return result;
}

Matrix4X4 Matrix4X4::RotationX4X4(const float& angle)
{
	Matrix4X4 result;
	
	result.Ligns[0].x = 1;
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;
	result.Ligns[0].w = 0;

	result.Ligns[1].x = 0;
	result.Ligns[1].y = cos((angle));
	result.Ligns[1].z = -sin((angle));
	result.Ligns[1].w = 0;

	result.Ligns[2].x = 0;
	result.Ligns[2].y = sin((angle));
	result.Ligns[2].z = cos((angle));
	result.Ligns[2].w = 0;

	result.Ligns[3].x = 0;
	result.Ligns[3].y = 0;
	result.Ligns[3].z = 0;
	result.Ligns[3].w = 1;
	

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

	result[0].w = translation.x;
	result[1].w = translation.y;
	result[2].w = translation.z;
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
	
	
	result.Ligns[0].x = cos((angle));
	result.Ligns[0].y = 0;
	result.Ligns[0].z = sin((angle));
	result.Ligns[0].w = 0;

	result.Ligns[1].x = 0;
	result.Ligns[1].y = 1;
	result.Ligns[1].z = 0;
	result.Ligns[1].w = 0;

	result.Ligns[2].x = -sin((angle));
	result.Ligns[2].y = 0;
	result.Ligns[2].z = cos((angle));
	result.Ligns[2].w = 0;

	result.Ligns[3].x = 0;
	result.Ligns[3].y = 0;
	result.Ligns[3].z = 0;
	result.Ligns[3].w = 1;
	
	return result;
}

// rad
Matrix4X4 Matrix4X4::RotationZ4X4(const float& angle)
{
	Matrix4X4 result;
	



	result.Ligns[0].x = cos((angle));
	result.Ligns[0].y = -sin((angle));
	result.Ligns[0].z = 0;
	result.Ligns[0].w = 0;

	result.Ligns[1].x = sin((angle));
	result.Ligns[1].y = cos((angle));
	result.Ligns[1].z = 0;
	result.Ligns[1].w = 0;

	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = 1;
	result.Ligns[2].w = 0;

	result.Ligns[3].x = 0;
	result.Ligns[3].y = 0;
	result.Ligns[3].z = 0;
	result.Ligns[3].w = 1;
	
	return result;
}

 Matrix4X4 Matrix4X4::operator*(const Matrix4X4& matrix) const
{

	Matrix4X4 result ;



	result.Ligns[0].x = this->Ligns[0].x * matrix[0].x + this->Ligns[0].y * matrix[1].x + this->Ligns[0].z * matrix[2].x + this->Ligns[0].w * matrix[3].x;
	result.Ligns[0].y = this->Ligns[0].x * matrix[0].y + this->Ligns[0].y * matrix[1].y + this->Ligns[0].z * matrix[2].y + this->Ligns[0].w * matrix[3].y;
	result.Ligns[0].z = this->Ligns[0].x * matrix[0].z + this->Ligns[0].y * matrix[1].z + this->Ligns[0].z * matrix[2].z + this->Ligns[0].w * matrix[3].z;
	result.Ligns[0].w = this->Ligns[0].x * matrix[0].w + this->Ligns[0].y * matrix[1].w + this->Ligns[0].z * matrix[2].w + this->Ligns[0].w * matrix[3].w;

	result.Ligns[1].x = this->Ligns[1].x * matrix[0].x + this->Ligns[1].y * matrix[1].x + this->Ligns[1].z * matrix[2].x + this->Ligns[1].w * matrix[3].x;
	result.Ligns[1].y = this->Ligns[1].x * matrix[0].y + this->Ligns[1].y * matrix[1].y + this->Ligns[1].z * matrix[2].y + this->Ligns[1].w * matrix[3].y;
	result.Ligns[1].z = this->Ligns[1].x * matrix[0].z + this->Ligns[1].y * matrix[1].z + this->Ligns[1].z * matrix[2].z + this->Ligns[1].w * matrix[3].z;
	result.Ligns[1].w = this->Ligns[1].x * matrix[0].w + this->Ligns[1].y * matrix[1].w + this->Ligns[1].z * matrix[2].w + this->Ligns[1].w * matrix[3].w;

	result.Ligns[2].x = this->Ligns[2].x * matrix[0].x + this->Ligns[2].y * matrix[1].x + this->Ligns[2].z * matrix[2].x + this->Ligns[2].w * matrix[3].x;
	result.Ligns[2].y = this->Ligns[2].x * matrix[0].y + this->Ligns[2].y * matrix[1].y + this->Ligns[2].z * matrix[2].y + this->Ligns[2].w * matrix[3].y;
	result.Ligns[2].z = this->Ligns[2].x * matrix[0].z + this->Ligns[2].y * matrix[1].z + this->Ligns[2].z * matrix[2].z + this->Ligns[2].w * matrix[3].z;
	result.Ligns[2].w = this->Ligns[2].x * matrix[0].w + this->Ligns[2].y * matrix[1].w + this->Ligns[2].z * matrix[2].w + this->Ligns[2].w * matrix[3].w;

	result.Ligns[3].x = this->Ligns[3].x * matrix[0].x + this->Ligns[3].y * matrix[1].x + this->Ligns[3].z * matrix[2].x + this->Ligns[3].w * matrix[3].x;
	result.Ligns[3].y = this->Ligns[3].x * matrix[0].y + this->Ligns[3].y * matrix[1].y + this->Ligns[3].z * matrix[2].y + this->Ligns[3].w * matrix[3].y;
	result.Ligns[3].z = this->Ligns[3].x * matrix[0].z + this->Ligns[3].y * matrix[1].z + this->Ligns[3].z * matrix[2].z + this->Ligns[3].w * matrix[3].z;
	result.Ligns[3].w = this->Ligns[3].x * matrix[0].w + this->Ligns[3].y * matrix[1].w + this->Ligns[3].z * matrix[2].w + this->Ligns[3].w * matrix[3].w;



	return result;

	
}


Vector4 ReturnLign(const Matrix4X4& matrix ,int index) 
{
	Vector4 vec;

	if(index == 0)
	{
		vec = Vector4(matrix.Ligns[0].x, matrix.Ligns[1].x, matrix.Ligns[2].x, matrix.Ligns[3].x);
	}
	else if(index == 1)
	{
		vec = Vector4(matrix.Ligns[0].y, matrix.Ligns[1].y, matrix.Ligns[2].y, matrix.Ligns[3].y);
	}else if(index == 2)
	{
		vec = Vector4(matrix.Ligns[0].z, matrix.Ligns[1].z, matrix.Ligns[2].z, matrix.Ligns[3].z);
	}
	else if (index == 3)
	{
		vec = Vector4(matrix.Ligns[0].w, matrix.Ligns[1].w, matrix.Ligns[2].w, matrix.Ligns[3].w);
	}
	else
	{
		return vec;
	}

	return vec;
}

Matrix4X4 Matrix4X4::Identity()
{
	Matrix4X4 result;

	result.Ligns[0].x = 1;
	result.Ligns[0].y = 0;
	result.Ligns[0].z = 0;
	result.Ligns[0].w = 0;

	result.Ligns[1].x = 0;
	result.Ligns[1].y = 1;
	result.Ligns[1].z = 0;
	result.Ligns[1].w = 0;

	result.Ligns[2].x = 0;
	result.Ligns[2].y = 0;
	result.Ligns[2].z = 1;
	result.Ligns[2].w = 0;

	result.Ligns[3].x = 0;
	result.Ligns[3].y = 0;
	result.Ligns[3].z = 0;
	result.Ligns[3].w = 1;


	return result;
}

Matrix4X4 Matrix4X4::Transposate() const
{
	Matrix4X4 result;

	result[0].x = Ligns[0].x ; result[0].y = Ligns[1].x ; result[0].z = Ligns[2].x ; result[0].w = Ligns[3].x ;
	result[1].x = Ligns[0].y ; result[1].y = Ligns[1].y ; result[1].z = Ligns[2].y ; result[1].w = Ligns[3].y ;
	result[2].x = Ligns[0].z ; result[2].y = Ligns[1].z ; result[2].z = Ligns[2].z ; result[2].w = Ligns[3].z ;
	result[3].x = Ligns[0].w ; result[3].y = Ligns[1].w ; result[3].z = Ligns[2].w ; result[3].w = Ligns[3].w ;






	return result;
}

Vector4 Matrix4X4::operator[](const int& i) const
{
	return Ligns[i];
}

Vector4& Matrix4X4::operator[](const int& i)
{
	return Ligns[i];
}

Matrix4X4 Matrix4X4::LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 zaxis = (at - eye).Normalize();
	Vector3 xaxis = (up.CrossProduct(zaxis)).Normalize();
	Vector3 yaxis = zaxis.CrossProduct(xaxis);

	zaxis = -zaxis;

	Matrix4X4 LookAtMatrix;

	LookAtMatrix.Ligns[0].x = xaxis.x;
	LookAtMatrix.Ligns[0].y = yaxis.x;
	LookAtMatrix.Ligns[0].z = zaxis.x;
	LookAtMatrix.Ligns[0].w = 0;

	LookAtMatrix.Ligns[1].x = xaxis.y;
	LookAtMatrix.Ligns[1].y = yaxis.y;
	LookAtMatrix.Ligns[1].z = zaxis.y;
	LookAtMatrix.Ligns[1].w = 0;

	LookAtMatrix.Ligns[2].x = xaxis.z;
	LookAtMatrix.Ligns[2].y = yaxis.z;
	LookAtMatrix.Ligns[2].z = zaxis.z;
	LookAtMatrix.Ligns[2].w = 0;

	LookAtMatrix.Ligns[3].x = -(xaxis.DotProduct(eye));
	LookAtMatrix.Ligns[3].y = -(yaxis.DotProduct(eye));	
	LookAtMatrix.Ligns[3].z = -(zaxis.DotProduct(eye));
	LookAtMatrix.Ligns[3].w = 1;


	return LookAtMatrix;
}



const float* Matrix4X4::GetPtr() const
{
	return &Ligns[0].x;
}

Matrix4X4::Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
{
	Ligns[0] = a;
	Ligns[1] = b;
	Ligns[2] = c;
	Ligns[3] = d;
}

Matrix4X4 Rotate(const Matrix4X4& matrix, const Vector3& angle)
{
	return  Matrix4X4().Identity() *  (Matrix4X4().RotationMatrix4X4(angle) * matrix);

}

Matrix4X4 Translate(const Matrix4X4& matrix, const Vector3& angle)
{
	Matrix4X4 result = matrix;
	result.Ligns[3] += angle;


	return result;
}



Matrix4X4::Matrix4X4()
{
	for (size_t i = 0; i < 4; i++)
	{
		Ligns[i].x = 0;
		Ligns[i].y = 0;
		Ligns[i].z = 0;
		Ligns[i].w = 0;

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
	for (size_t i = 0; i < 4; i++)
	{
		stream << maxtrix.Ligns[i].x << " " << maxtrix.Ligns[i].y << " " << maxtrix.Ligns[i].z << " " << maxtrix.Ligns[i].w << " ";
		stream << '\n';

	}



	return stream;
}