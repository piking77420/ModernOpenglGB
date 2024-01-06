#pragma once
#include <iostream>
#include "Vector4.h"
#include "Matrix3X3.h"
#include "Quaternion.h"
#include "Mathf.h"

class Vector3;
class Matrix;

/**
	*@class Matrix4X4
	*@brief Matrix4X4 ColumnsMajor \n
	* m00 m10 m20 m30 \n
	* m01 m11 m21 m31 \n
	* m02 m12 m22 m32 \n
	* m03 m13 m23 m33 \n
	*/



class Matrix4X4
{
public:

	/**
	* @var Columns
	Data of the Matrix
	*/
	Vector4 Columns[4];

#pragma region GraphicMatrix

	/**
	* @fn static Matrix4X4 PerspectiveMatrix(const float fov, const float aspect, const float Near,const float Far);
	* @brief Projection Matrix.
	* @param fov the field of wiew in radian
	*/
	static inline Matrix4X4 PerspectiveMatrix(const float fov, const float aspect, const float Near,const float Far)
	{
	
		
		float fFovRad = 1.0f / std::tanf(fov * 0.5f);
		float zdiff = Near - Far;

		float r00 = fFovRad / aspect;
		float r11 = fFovRad;

		float r22 = (Far + Near) / zdiff;
		float r32 = (2 * Far * Near) / zdiff;
		
		return {
				{r00, 0.f, 0.f,0.f },
				{0.f, r11, 0.f,0.f },
				{0.f, 0.f, r22, -1.0f},
				{0, 0,r32, 0}
		}; 

	}
	/**
	* @fn static Matrix4X4 OrthoGraphicMatrix( float top , float bot , float right ,float left , float Near,  float Far);
	* @brief OrthoGraphicProjection.
	*/
	constexpr static inline Matrix4X4 OrthoGraphicMatrix(float left, float right, float bottom, float top, float zNear, float zFar) 
	{
		float topBottomDiff = top - bottom;
		float rightLeftDiff = right - left;
		float farMinusNear = zFar - zNear;

		float r00 = 2.0f / rightLeftDiff;
		float r11 = 2.0f / topBottomDiff;
		float r22 = -2.0f / farMinusNear;

		float r03 = -(right + left) / rightLeftDiff;
		float r13 = -(top + bottom) / topBottomDiff;
		float r23 = -(zFar + zNear) / farMinusNear;

		return {
				{r00, 0.f, 0.f,0.f },
				{0.f, r11, 0.f,0.f },
				{0.f, 0.f, r22, 0.f},
				{r03, r13,r23, 1.f}
		};
	}


	constexpr inline float GetTrace() 
	{
		float x = Columns[0][0];
		float y = Columns[1][1];
		float z = Columns[2][2];
		float w = Columns[3][3];

		return x + y + z + w;
	}


	static inline bool DecomposeMatrix(const Matrix4X4& matrix, Vector3& tranlation , Vector3& rotation , Vector3& scale )
	{

		 // From Hazel github page 
		// https://github.com/TheCherno/Hazel/blob/5e20b232b749a8f1339e32074c254c44d7c9c263/Hazel/src/Hazel/Math/Math.cpp#L46

		using namespace Math;

		Matrix4X4 LocalMatrix(matrix);

		if (epsilonEqual(LocalMatrix[3][3], 0.f, Epsilon()))
			return false;

		// First, isolate perspective.  This is the messiest.
		if (
			epsilonNotEqual(LocalMatrix[0][3], 0.f, Epsilon()) ||
			epsilonNotEqual(LocalMatrix[1][3], 0.f, Epsilon()) ||
			epsilonNotEqual(LocalMatrix[2][3], 0.f, Epsilon()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = 0.f;
			LocalMatrix[3][3] = 1.f;
		}

		tranlation = static_cast<Vector3>(LocalMatrix[3]);

		LocalMatrix[3] = Vector4(0.f, 0.f, 0.f, LocalMatrix[3].w);


		Vector3 Row[3], Pdum3;

		// Now get scale and shear.
		for (uint32_t i = 0; i < 3; ++i)
			for (uint32_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		scale.x = Row[0].Norm();
		Row[0] = Vector3::Scale(Row[0], 1.f);
		scale.y = Row[1].Norm();
		Row[1] = Vector3::Scale(Row[1], 1.f);
		scale.z = Row[2].Norm();
		Row[2] = Vector3::Scale(Row[2], 1.f);



		rotation.y = std::asin(-Row[0][2]);
		if (std::cos(rotation.y) != 0) {
			rotation.x = std::atan2(Row[1][2], Row[2][2]);
			rotation.z = std::atan2(Row[0][1], Row[0][0]);
		}
		else {
			rotation.x = std::atan2(-Row[2][0], Row[1][1]);
			rotation.z = 0;
		}


		return true;
	}


	/**
	* @fn static Matrix4X4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);;
	* @brief OrthoGraphicProjection.
	*/
	static inline Matrix4X4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Vector3 f = (at - eye).Normalize();
		Vector3 s = Vector3::CrossProduct(f, up).Normalize();
		Vector3 u = Vector3::CrossProduct(s, f);


		Matrix4X4 Result(Matrix4X4::Identity());

		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -Vector3::DotProduct(s, eye);
		Result[3][1] = -Vector3::DotProduct(u, eye);
		Result[3][2] = Vector3::DotProduct(f, eye);

		return Result;
	}
#pragma endregion

#pragma region TransformMatrix
	// rad
	static Matrix4X4 RotationZ4X4(const float& angle);

	// rad
	static Matrix4X4 RotationY4X4(const float& angle);

	// rad
	static Matrix4X4 RotationX4X4(const float& angle);


	// rad
	constexpr static Matrix4X4 RotationMatrix4X4(const Vector3& angle)
	{
		return RotationZ4X4(angle.z) * RotationY4X4(angle.y) * RotationX4X4(angle.x);
	}

	constexpr inline static Matrix4X4 TranslateMatrix4X4(const Vector3& translation)
	{
		return {
		{1.f, 0.f, 0.f,0.f },
		{0.f, 1.f, 0.f,0.f },
		{0.f, 0.f, 1.f, 0.f},
		{translation.x, translation.y,translation.z, 1.f}
		};
	}

	constexpr inline static Matrix4X4 ScalingMatrix4X4(const Vector3& ScalingFactor)
	{
		return {
		{ScalingFactor.x, 0.f, 0.f,0.f },
		{0.f, ScalingFactor.y, 0.f,0.f },
		{0.f, 0.f, ScalingFactor.z, 0.f},
		{0, 0,0 , 1.f}
		};
	}

	constexpr static inline Matrix4X4 TRS(const Vector3& translation , const Vector3& angle , const Vector3& scaling)
	{
		return (TranslateMatrix4X4(translation) * (RotationMatrix4X4(angle) * ScalingMatrix4X4(scaling)));
	}
	constexpr static inline Matrix4X4 TRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scaling)
	{
		return (TranslateMatrix4X4(translation) * (Quaternion::ToRotationMatrix4X4(rotation.Normalize()) * ScalingMatrix4X4(scaling)));
	}

#pragma endregion



	constexpr inline static Matrix4X4 Identity()
	{
		return {
					{1.f, 0.f, 0.f,0.f },
					{0.f, 1.f, 0.f,0.f },
					{0.f, 0.f, 1.f, 0.f},
					{0.f, 0.f,0.f, 1.f}
		};
	}

	Matrix4X4 Invert() const;
	constexpr inline Matrix4X4 Transpose() const 
	{
		Matrix4X4 result;

		result[0].x = Columns[0].x; result[0].y = Columns[1].x; result[0].z = Columns[2].x; result[0].w = Columns[3].x;
		result[1].x = Columns[0].y; result[1].y = Columns[1].y; result[1].z = Columns[2].y; result[1].w = Columns[3].y;
		result[2].x = Columns[0].z; result[2].y = Columns[1].z; result[2].z = Columns[2].z; result[2].w = Columns[3].z;
		result[3].x = Columns[0].w; result[3].y = Columns[1].w; result[3].z = Columns[2].w; result[3].w = Columns[3].w;


		return result;
	}
	static inline float Determinant(const Matrix4X4& matrix);

	constexpr inline const float* GetPtr() const
	{
		return &Columns[0].x;
	}
	constexpr inline float* SetPtr()
	{
		return &Columns[0].x;
	}


	static inline Matrix4X4 AdjoinMatrix(const Matrix4X4& matrix);
	
#pragma region Operator 
	constexpr inline Matrix4X4 operator*(const Matrix4X4& matrix) const
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


	Vector4 operator*(const Vector4& Row1)
	{
		Vector4 resutl;
		Matrix4X4 m = Transpose();

		resutl.x = Vector4::DotProduct(m[0], Row1);
		resutl.y = Vector4::DotProduct(m[1], Row1);
		resutl.z = Vector4::DotProduct(m[2], Row1);
		resutl.w = Vector4::DotProduct(m[3], Row1);


		return resutl;
	}

	Matrix4X4 operator*(float value)
	{
		
		Matrix4X4 m = *this;

		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 4; k++) 
			{
				m[i][k] *= value;
			}
		}

		return m;
	}


	constexpr inline const Vector4& operator[](int i) const 
	{
		return Columns[i];
	}
	constexpr inline Vector4& operator[](int i)
	{
		return Columns[i];
	}
	explicit operator Matrix();
#pragma endregion

	constexpr Matrix4X4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
	{
		Columns[0] = a;
		Columns[1] = b;
		Columns[2] = c;
		Columns[3] = d;
	}
	constexpr Matrix4X4() = default;
	

private:

};


std::ostream& operator<<(std::ostream& stream, const  Matrix4X4& maxtrix);
