#include "Matrix4X4.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "Mathf.h"









Matrix4X4 Matrix4X4::ViewMatrix(const Vector3& Left, const Vector3& Up, const Vector3& Forward, const Vector3& Translation)
{
	Matrix4X4 result;

	result.Coloms[0].x = Left.x;
	result.Coloms[0].y = Left.y;
	result.Coloms[0].z = Left.z;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = Up.x;
	result.Coloms[1].y = Up.y;
	result.Coloms[1].z = Up.z;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = Forward.x;
	result.Coloms[2].y = Forward.y;
	result.Coloms[2].z = Forward.z;
	result.Coloms[2].w = 0;

	result.Coloms[3].x = Translation.x;
	result.Coloms[3].y = Translation.y;
	result.Coloms[3].z = Translation.z;
	result.Coloms[3].w = 1;

	return result;
}

// fov int degres  , aspect widh/height , near 0.1 , far 1000.f
Matrix4X4 Matrix4X4::ProjectionMatrix(const float& fov, const float& aspect, const float& Near, const float& Far)
{
	Matrix4X4 result;



	float fFovRad = 1.0f / std::tan((fov / 180.f * 3.14159f) * 0.5f);

	float zdiff = Near - Far ;


	result.Coloms[0].x = fFovRad / aspect;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = 0;
	result.Coloms[1].y = fFovRad;
	result.Coloms[1].z = 0;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = (Far + Near) / zdiff;
	result.Coloms[2].w = -1.0f;

	result.Coloms[3].x = 0;
	result.Coloms[3].y = 0 ;
	result.Coloms[3].z = (2 * Far * Near) / zdiff;
	result.Coloms[3].w = 0;

	return result;

}

Matrix4X4 Matrix4X4::OrthoGraphicMatrix(float top, float bot, float right, float left, float Near, float Far)
{

	Matrix4X4 result;

	float topbottomDiff = top - bot;
	float rightLeftDiff = left - right;

	result.Coloms[0].x = 2.f  / right - left ;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = 0;
	result.Coloms[1].y =  2.f / (top - bot) ;
	result.Coloms[1].z = 0;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1.f / (Far - Near  );
	result.Coloms[2].w = 0;

	result.Coloms[3].x = (left + right )/ (left - right);
	result.Coloms[3].y = -(top + bot )/ (bot - top);
	result.Coloms[3].z = (Near) / (Near - Far);
	result.Coloms[3].w = 1.f;


	return result;
}


/* 
Matrix4X4 Matrix4X4::Ortho(float left, float right, float bottom, float, float)
{
	Matrix4X4 result;

	result.Rows[0].x = (1.f / (aspect * tan(fov / 2)));
	result.Rows[0].y = 0;
	result.Rows[0].z = 0;
	result.Rows[0].w = 0;

	result.Rows[1].x = 0;
	result.Rows[1].y = (1.f / tan(fov / 2.f));
	result.Rows[1].z = 0;
	result.Rows[1].w = 0;

	result.Rows[2].x = 0;
	result.Rows[2].y = 0;
	result.Rows[2].z = -((Far + Near) / (Far - Near));
	result.Rows[2].w = -1;

	result.Rows[3].x = 0;
	result.Rows[3].y = 0;
	result.Rows[3].z = -((2 * Far * Near) / (Far - Near));
	result.Rows[3].w = 0;

	return result;
}*/

Vector3 Matrix4X4::GetPos()
{
	return Vector3(Coloms[3]);
}

Matrix4X4 Matrix4X4::ScalingMatrix4X4(const Vector3& ScalingFactor)
{
	Matrix4X4 result;
	
	result.Coloms[0].x = ScalingFactor.x;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = 0;
	result.Coloms[1].y = ScalingFactor.y;
	result.Coloms[1].z = 0;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = ScalingFactor.z;
	result.Coloms[2].w = 0;

	result.Coloms[3].x = 0;
	result.Coloms[3].y = 0;
	result.Coloms[3].z = 0;
	result.Coloms[3].w = 1;
	
	return result;
}

Matrix4X4 Matrix4X4::RotationX4X4(const float& angle)
{
	Matrix4X4 result;
	
	result.Coloms[0].x = 1;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = 0;
	result.Coloms[1].y = cos((angle));
	result.Coloms[1].z = sin((angle));
	result.Coloms[1].w = 0;

	result.Coloms[2].x = 0;
	result.Coloms[2].y = -sin((angle));
	result.Coloms[2].z = cos((angle));
	result.Coloms[2].w = 0;

	result.Coloms[3].x = 0;
	result.Coloms[3].y = 0;
	result.Coloms[3].z = 0;
	result.Coloms[3].w = 1;
	

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
	
	
	result.Coloms[0].x = cos((angle));
	result.Coloms[0].y = 0;
	result.Coloms[0].z = -sin((angle));
	result.Coloms[0].w = 0;

	result.Coloms[1].x = 0;
	result.Coloms[1].y = 1;
	result.Coloms[1].z = 0;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = sin((angle));
	result.Coloms[2].y = 0;
	result.Coloms[2].z = cos((angle));
	result.Coloms[2].w = 0;

	result.Coloms[3].x = 0;
	result.Coloms[3].y = 0;
	result.Coloms[3].z = 0;
	result.Coloms[3].w = 1;
	
	return result;
}

// rad
Matrix4X4 Matrix4X4::RotationZ4X4(const float& angle)
{
	Matrix4X4 result;
	



	result.Coloms[0].x = cos((angle));
	result.Coloms[0].y = sin((angle));
	result.Coloms[0].z = 0;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = -sin((angle));
	result.Coloms[1].y = cos((angle));
	result.Coloms[1].z = 0;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;
	result.Coloms[2].w = 0;

	result.Coloms[3].x = 0;
	result.Coloms[3].y = 0;
	result.Coloms[3].z = 0;
	result.Coloms[3].w = 1;
	
	return result;
}

 Matrix4X4 Matrix4X4::operator*(const Matrix4X4& matrix) const
{
	
	
	

	Matrix4X4 trans = this->Transposate();

	Matrix4X4 result ;



	result.Coloms[0].x = trans[0].DotProduct(matrix.Coloms[0]);
	result.Coloms[0].y = trans[0].DotProduct(matrix.Coloms[1]);
	result.Coloms[0].z = trans[0].DotProduct(matrix.Coloms[2]);
	result.Coloms[0].w = trans[0].DotProduct(matrix.Coloms[3]);

	result.Coloms[1].x = trans[1].DotProduct(matrix.Coloms[0]);
	result.Coloms[1].y = trans[1].DotProduct(matrix.Coloms[1]);
	result.Coloms[1].z = trans[1].DotProduct(matrix.Coloms[2]);
	result.Coloms[1].w = trans[1].DotProduct(matrix.Coloms[3]);

	result.Coloms[2].x = trans[2].DotProduct(matrix.Coloms[0]);
	result.Coloms[2].y = trans[2].DotProduct(matrix.Coloms[1]);
	result.Coloms[2].z = trans[2].DotProduct(matrix.Coloms[2]);
	result.Coloms[2].w = trans[2].DotProduct(matrix.Coloms[3]);

	result.Coloms[3].x = trans[3].DotProduct(matrix.Coloms[0]);
	result.Coloms[3].y = trans[3].DotProduct(matrix.Coloms[1]);
	result.Coloms[3].z = trans[3].DotProduct(matrix.Coloms[2]);
	result.Coloms[3].w = trans[3].DotProduct(matrix.Coloms[3]);



	return result.Transposate();

	
}


Vector4 ReturnLign(const Matrix4X4& matrix ,int index) 
{
	Vector4 vec;

	if(index == 0)
	{
		vec = Vector4(matrix.Coloms[0].x, matrix.Coloms[1].x, matrix.Coloms[2].x, matrix.Coloms[3].x);
	}
	else if(index == 1)
	{
		vec = Vector4(matrix.Coloms[0].y, matrix.Coloms[1].y, matrix.Coloms[2].y, matrix.Coloms[3].y);
	}else if(index == 2)
	{
		vec = Vector4(matrix.Coloms[0].z, matrix.Coloms[1].z, matrix.Coloms[2].z, matrix.Coloms[3].z);
	}
	else if (index == 3)
	{
		vec = Vector4(matrix.Coloms[0].w, matrix.Coloms[1].w, matrix.Coloms[2].w, matrix.Coloms[3].w);
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

	result.Coloms[0].x = 1;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;
	result.Coloms[0].w = 0;

	result.Coloms[1].x = 0;
	result.Coloms[1].y = 1;
	result.Coloms[1].z = 0;
	result.Coloms[1].w = 0;

	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;
	result.Coloms[2].w = 0;

	result.Coloms[3].x = 0;
	result.Coloms[3].y = 0;
	result.Coloms[3].z = 0;
	result.Coloms[3].w = 1;


	return result;
}

Matrix4X4 Matrix4X4::Transposate() const
{
	Matrix4X4 result;

	for (size_t i = 0; i < 4; i++)
	{
		result.Coloms[i] = ReturnLign(*this, i);
	}

	return result;
}

Vector4 Matrix4X4::operator[](const int& i) const
{
	return Coloms[i];
}

Vector4& Matrix4X4::operator[](const int& i)
{
	return Coloms[i];
}

Matrix4X4 Matrix4X4::LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 zaxis = (at - eye).Normalize();
	Vector3 xaxis = (up.CrossProduct(zaxis)).Normalize();
	Vector3 yaxis = zaxis.CrossProduct(xaxis);

	zaxis = -zaxis;

	Matrix4X4 LookAtMatrix;

	LookAtMatrix.Coloms[0].x = xaxis.x;
	LookAtMatrix.Coloms[0].y = yaxis.x;
	LookAtMatrix.Coloms[0].z = zaxis.x;
	LookAtMatrix.Coloms[0].w = 0;

	LookAtMatrix.Coloms[1].x = xaxis.y;
	LookAtMatrix.Coloms[1].y = yaxis.y;
	LookAtMatrix.Coloms[1].z = zaxis.y;
	LookAtMatrix.Coloms[1].w = 0;

	LookAtMatrix.Coloms[2].x = xaxis.z;
	LookAtMatrix.Coloms[2].y = yaxis.z;
	LookAtMatrix.Coloms[2].z = zaxis.z;
	LookAtMatrix.Coloms[2].w = 0;

	LookAtMatrix.Coloms[3].x = -(xaxis.DotProduct(eye));
	LookAtMatrix.Coloms[3].y = -(yaxis.DotProduct(eye));	
	LookAtMatrix.Coloms[3].z = -(zaxis.DotProduct(eye));
	LookAtMatrix.Coloms[3].w = 1;


	return LookAtMatrix;
}



const float* Matrix4X4::GetPtr() const
{
	return &Coloms[0].x;
}

Matrix4X4::Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
{
	Coloms[0] = a;
	Coloms[1] = b;
	Coloms[2] = c;
	Coloms[3] = d;
}

Matrix4X4 Rotate(const Matrix4X4& matrix, const Vector3& angle)
{
	return  Matrix4X4().Identity() *  (Matrix4X4().RotationMatrix4X4(angle) * matrix);

}

Matrix4X4 Translate(const Matrix4X4& matrix, const Vector3& angle)
{
	Matrix4X4 result = matrix;
	result.Coloms[3] += angle;


	return result;
}



Matrix4X4::Matrix4X4()
{
	for (size_t i = 0; i < 4; i++)
	{
		Coloms[i].x = 0;
		Coloms[i].y = 0;
		Coloms[i].z = 0;
		Coloms[i].w = 0;

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
		stream << maxtrix.Coloms[i].x << " ";
	}
	stream << '\n';
	for (size_t i = 0; i < 4; i++)
	{
		stream << maxtrix.Coloms[i].y << " ";
	}
	stream << '\n';

	for (size_t i = 0; i < 4; i++)
	{
		stream << maxtrix.Coloms[i].z << " ";
	}
	stream << '\n';

	for (size_t i = 0; i < 4; i++)
	{
		stream << maxtrix.Coloms[i].w << " ";
	}
	stream << '\n';
	return stream;
}