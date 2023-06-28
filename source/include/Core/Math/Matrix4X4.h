#pragma once
#include "Vector4.h"
#include "Matrix3X3.h"
#include "Mathf.h"
#include <math.h>
#include <iostream>



class Matrix4X4
{
public:

	

	Vector4 Columns[4];

	static Matrix4X4 ProjectionMatrix(const float& fov, const float& aspect, const float& Near,const float& Far);
	static Matrix4X4 OrthoGraphicMatrix( float top , float bot , float right ,float left , float Near,  float Far);
	static Matrix4X4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);


	Vector3 GetPos();
	//Matrix4X4 Ortho(float left, float right, float bottom, float near, float far);
	static Matrix4X4 ScalingMatrix4X4(const Vector3& ScalingFactor);

	// rad
	static Matrix4X4 RotationZ4X4(const float& angle);

	// rad
	static Matrix4X4 RotationY4X4(const float& angle);

	// rad
	static Matrix4X4 RotationX4X4(const float& angle);


	// rad
	static Matrix4X4 RotationMatrix4X4(const Vector3& angle);

	static Matrix4X4 TranslateMatrix4X4(const Vector3& translation);

	static Matrix4X4 TRS(const Vector3& translation , const Vector3& angle , const Vector3& scaling);

	Matrix4X4 operator*(const Matrix4X4& matrix) const;


	static Matrix4X4 Identity();
	Matrix4X4 Transposate() const;


	Vector4 operator[](const int& i ) const ;

	Vector4& operator[](const int& i) ;


	const float* GetPtr() const;

	Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d);
	



	explicit operator Matrix();


	Matrix4X4();
	~Matrix4X4();

private:

};


Matrix4X4 Translate(const Matrix4X4& matrix, const Vector3& angle);
Matrix4X4 Rotate(const Matrix4X4& matrix, const Vector3& angle);



 Vector4 operator*(const Matrix4X4& matrix, const Vector4& Row1);

 Vector4 operator*(const Vector4& Row1,const Matrix4X4& matrix);




std::ostream& operator<<(std::ostream& stream, const  Matrix4X4& maxtrix);
