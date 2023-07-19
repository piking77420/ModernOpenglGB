#include "Matrix4X4.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"







// fov int degres  , aspect widh/height , near 0.1 , far 1000.f
Matrix4X4 Matrix4X4::ProjectionMatrix(const float& fov, const float& aspect, const float& Near, const float& Far)
{
	Matrix4X4 result;



	float fFovRad = 1.0f / std::tan((fov / 180.f * 3.14159f) * 0.5f);

	float zdiff = Near - Far;


	result.Colums[0].x = fFovRad / aspect;
	result.Colums[0].y = 0;
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = fFovRad;
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = 0;
	result.Colums[2].z = (Far + Near) / zdiff;
	result.Colums[2].w = -1.0f;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = (2 * Far * Near) / zdiff;
	result.Colums[3].w = 0;

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
	return Vector3(Colums[3]);
}

Matrix4X4 Matrix4X4::ScalingMatrix4X4(const Vector3& ScalingFactor)
{
	Matrix4X4 result;
	
	result.Colums[0].x = ScalingFactor.x;
	result.Colums[0].y = 0;
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = ScalingFactor.y;
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = 0;
	result.Colums[2].z = ScalingFactor.z;
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	
	return result;
}

Matrix4X4 Matrix4X4::RotationX4X4(const float& angle)
{
	Matrix4X4 result;
	
	result.Colums[0].x = 1;
	result.Colums[0].y = 0;
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = cos((angle));
	result.Colums[1].z = sin((angle));
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = -sin((angle));
	result.Colums[2].z = cos((angle));
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	

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

Matrix4X4 Matrix4X4::TRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scaling)
{

	Matrix4X4 translationMatrix = TranslateMatrix4X4(translation);
	Matrix4X4 rotationMatrix = Quaternion::ToMatrix4X4(rotation);
	Matrix4X4 scalingMatrix = ScalingMatrix4X4(scaling);
	return (translationMatrix * (rotationMatrix * scalingMatrix));

	return Matrix4X4();
}


// rad
Matrix4X4 Matrix4X4::RotationY4X4(const float& angle)
{
	Matrix4X4 result;
	

	result.Colums[0].x = cos((angle));
	result.Colums[0].y = 0;
	result.Colums[0].z = -sin((angle));
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = 1;
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = sin((angle));
	result.Colums[2].y = 0;
	result.Colums[2].z = cos((angle));
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	
	return result;
}

// rad
Matrix4X4 Matrix4X4::RotationZ4X4(const float& angle)
{
	Matrix4X4 result;
	



	result.Colums[0].x = cos((angle));
	result.Colums[0].y = sin((angle));
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = -sin((angle));
	result.Colums[1].y = cos((angle));
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = 0;
	result.Colums[2].z = 1;
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	
	return result;
}

 Matrix4X4 Matrix4X4::operator*(const Matrix4X4& matrix) const
{

	 Matrix4X4 result;

	 result.Colums[0].x = this->Colums[0].x * matrix[0].x + this->Colums[1].x * matrix[0].y + this->Colums[2].x * matrix[0].z + this->Colums[3].x * matrix[0].w;
	 result.Colums[0].y = this->Colums[0].y * matrix[0].x + this->Colums[1].y * matrix[0].y + this->Colums[2].y * matrix[0].z + this->Colums[3].y * matrix[0].w;
	 result.Colums[0].z = this->Colums[0].z * matrix[0].x + this->Colums[1].z * matrix[0].y + this->Colums[2].z * matrix[0].z + this->Colums[3].z * matrix[0].w;
	 result.Colums[0].w = this->Colums[0].w * matrix[0].x + this->Colums[1].w * matrix[0].y + this->Colums[2].w * matrix[0].z + this->Colums[3].w * matrix[0].w;

	 result.Colums[1].x = this->Colums[0].x * matrix[1].x + this->Colums[1].x * matrix[1].y + this->Colums[2].x * matrix[1].z + this->Colums[3].x * matrix[1].w;
	 result.Colums[1].y = this->Colums[0].y * matrix[1].x + this->Colums[1].y * matrix[1].y + this->Colums[2].y * matrix[1].z + this->Colums[3].y * matrix[1].w;
	 result.Colums[1].z = this->Colums[0].z * matrix[1].x + this->Colums[1].z * matrix[1].y + this->Colums[2].z * matrix[1].z + this->Colums[3].z * matrix[1].w;
	 result.Colums[1].w = this->Colums[0].w * matrix[1].x + this->Colums[1].w * matrix[1].y + this->Colums[2].w * matrix[1].z + this->Colums[3].w * matrix[1].w;

	 result.Colums[2].x = this->Colums[0].x * matrix[2].x + this->Colums[1].x * matrix[2].y + this->Colums[2].x * matrix[2].z + this->Colums[3].x * matrix[2].w;
	 result.Colums[2].y = this->Colums[0].y * matrix[2].x + this->Colums[1].y * matrix[2].y + this->Colums[2].y * matrix[2].z + this->Colums[3].y * matrix[2].w;
	 result.Colums[2].z = this->Colums[0].z * matrix[2].x + this->Colums[1].z * matrix[2].y + this->Colums[2].z * matrix[2].z + this->Colums[3].z * matrix[2].w;
	 result.Colums[2].w = this->Colums[0].w * matrix[2].x + this->Colums[1].w * matrix[2].y + this->Colums[2].w * matrix[2].z + this->Colums[3].w * matrix[2].w;

	 result.Colums[3].x = this->Colums[0].x * matrix[3].x + this->Colums[1].x * matrix[3].y + this->Colums[2].x * matrix[3].z + this->Colums[3].x * matrix[3].w;
	 result.Colums[3].y = this->Colums[0].y * matrix[3].x + this->Colums[1].y * matrix[3].y + this->Colums[2].y * matrix[3].z + this->Colums[3].y * matrix[3].w;
	 result.Colums[3].z = this->Colums[0].z * matrix[3].x + this->Colums[1].z * matrix[3].y + this->Colums[2].z * matrix[3].z + this->Colums[3].z * matrix[3].w;
	 result.Colums[3].w = this->Colums[0].w * matrix[3].x + this->Colums[1].w * matrix[3].y + this->Colums[2].w * matrix[3].z + this->Colums[3].w * matrix[3].w;

	 return result;

	
}


Vector4 ReturnLign(const Matrix4X4& matrix ,int index) 
{
	Vector4 vec;

	if(index == 0)
	{
		vec = Vector4(matrix.Colums[0].x, matrix.Colums[1].x, matrix.Colums[2].x, matrix.Colums[3].x);
	}
	else if(index == 1)
	{
		vec = Vector4(matrix.Colums[0].y, matrix.Colums[1].y, matrix.Colums[2].y, matrix.Colums[3].y);
	}else if(index == 2)
	{
		vec = Vector4(matrix.Colums[0].z, matrix.Colums[1].z, matrix.Colums[2].z, matrix.Colums[3].z);
	}
	else if (index == 3)
	{
		vec = Vector4(matrix.Colums[0].w, matrix.Colums[1].w, matrix.Colums[2].w, matrix.Colums[3].w);
	}
	else
	{
		return vec;
	}

	return vec;
}

Matrix4X4 Matrix4X4::Invert()  
{
	Matrix m = (Matrix)*this;

	m = m.Invert();

	return (Matrix4X4)m;
}

Matrix4X4 Matrix4X4::Identity()
{
	Matrix4X4 result;

	result.Colums[0].x = 1;
	result.Colums[0].y = 0;
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = 1;
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = 0;
	result.Colums[2].z = 1;
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;


	return result;
}

Matrix4X4 Matrix4X4::Transposate() const
{
	Matrix4X4 result;

	result[0].x = Colums[0].x ; result[0].y = Colums[1].x ; result[0].z = Colums[2].x ; result[0].w = Colums[3].x ;
	result[1].x = Colums[0].y ; result[1].y = Colums[1].y ; result[1].z = Colums[2].y ; result[1].w = Colums[3].y ;
	result[2].x = Colums[0].z ; result[2].y = Colums[1].z ; result[2].z = Colums[2].z ; result[2].w = Colums[3].z ;
	result[3].x = Colums[0].w ; result[3].y = Colums[1].w ; result[3].z = Colums[2].w ; result[3].w = Colums[3].w ;






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
	return Colums[i];
}

Vector4& Matrix4X4::operator[](const int& i)
{
	return Colums[i];
}

Matrix4X4 Matrix4X4::LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 zaxis = (at - eye).Normalize();
	Vector3 xaxis = Vector3::CrossProduct(up,zaxis).Normalize();
	Vector3 yaxis = Vector3::CrossProduct(zaxis,xaxis);

	zaxis = -zaxis;

	Matrix4X4 LookAtMatrix;

	LookAtMatrix.Colums[0].x = xaxis.x;
	LookAtMatrix.Colums[0].y = yaxis.x;
	LookAtMatrix.Colums[0].z = zaxis.x;
	LookAtMatrix.Colums[0].w = 0;

	LookAtMatrix.Colums[1].x = xaxis.y;
	LookAtMatrix.Colums[1].y = yaxis.y;
	LookAtMatrix.Colums[1].z = zaxis.y;
	LookAtMatrix.Colums[1].w = 0;

	LookAtMatrix.Colums[2].x = xaxis.z;
	LookAtMatrix.Colums[2].y = yaxis.z;
	LookAtMatrix.Colums[2].z = zaxis.z;
	LookAtMatrix.Colums[2].w = 0;

	LookAtMatrix.Colums[3].x = -(Vector3::DotProduct(xaxis,eye));
	LookAtMatrix.Colums[3].y = -(Vector3::DotProduct(yaxis, eye));
	LookAtMatrix.Colums[3].z = -(Vector3::DotProduct(zaxis,eye));
	LookAtMatrix.Colums[3].w = 1;


	return LookAtMatrix;


}



const float* Matrix4X4::GetPtr() const
{
	return &Colums[0].x;
}

float* Matrix4X4::SetPtr()
{
	return &Colums[0].x;
}

Matrix4X4::Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
{
	Colums[0] = a;
	Colums[1] = b;
	Colums[2] = c;
	Colums[3] = d;
}

Matrix4X4 Rotate(const Matrix4X4& matrix, const Vector3& angle)
{
	return  Matrix4X4().Identity() *  (Matrix4X4().RotationMatrix4X4(angle) * matrix);

}

Matrix4X4 Translate(const Matrix4X4& matrix, const Vector3& angle)
{
	Matrix4X4 result = matrix;
	result.Colums[3] += angle;


	return result;
}

Matrix4X4::operator Matrix()
{
	Matrix result = Matrix(4);


	for (size_t i = 0; i < 4; i++)
	{
		for (size_t y = 0; y < 4; y++)
		{
			result[i][y] = Colums[y][i];

		}
	}

	return result;
}

Matrix4X4::Matrix4X4(const std::initializer_list<float>& values)
{
	if (values.size() > 16)
		*this = Identity();

	float* data = SetPtr();

	int i = 0;
	for (const auto& value : values) {
		data[i] = value;
		i++;
	}

}





Matrix4X4::Matrix4X4()
{
	for (size_t i = 0; i < 4; i++)
	{
		Colums[i].x = 0;
		Colums[i].y = 0;
		Colums[i].z = 0;
		Colums[i].w = 0;

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

	for (short int i = 0; i < 4; i++)
	{
		for (short int k = 0;k < 4;k++)
		{
			float value = maxtrix.Colums[k][i];
			if (value > -0.0002 && value < 0.0002)
				value = 0;

			stream << value << " ";
		}
		stream << '\n';
	}
	/*
	stream << maxtrix.Colums[0].x << " " << maxtrix.Colums[1].x << " " << maxtrix.Colums[2].x << " " << maxtrix.Colums[3].x << " ";
	stream << '\n';
	stream << maxtrix.Colums[0].y << " " << maxtrix.Colums[1].y << " " << maxtrix.Colums[2].y << " " << maxtrix.Colums[3].y << " ";
	stream << '\n';
	stream << maxtrix.Colums[0].z << " " << maxtrix.Colums[1].z << " " << maxtrix.Colums[2].z << " " << maxtrix.Colums[3].z << " ";
	stream << '\n';
	stream << maxtrix.Colums[0].w << " " << maxtrix.Colums[1].w << " " << maxtrix.Colums[2].w << " " << maxtrix.Colums[3].w << " ";
	*/
	return stream;
}