#include "Mathf.h"


namespace MathTransform
{
	
	static Vector3 GetPos(const Matrix4X4& tranformMatrix)
	{
		return static_cast<Vector3>(tranformMatrix[3]);
	}


	static Matrix4X4 TRS(const Vector3& translation, const Vector3& angle, const Vector3& scaling)
	{
		Matrix4X4 translationMatrix = Matrix4X4::TranslateMatrix4X4(translation);
		Matrix4X4 rotationMatrix = Matrix4X4::RotationMatrix4X4(angle);
		Matrix4X4 scalingMatrix = Matrix4X4::ScalingMatrix4X4(scaling);
		return (translationMatrix * (rotationMatrix * scalingMatrix));
	}
	static Matrix4X4 TRS(const Vector3& translation, const Quaternion& rotation, const Vector3& scaling)
	{
		Matrix4X4 translationMatrix = Matrix4X4::TranslateMatrix4X4(translation);
		Matrix4X4 rotationMatrix = Quaternion::ToMatrix4X4(rotation);
		Matrix4X4 scalingMatrix = Matrix4X4::ScalingMatrix4X4(scaling);
		return (translationMatrix * (rotationMatrix * scalingMatrix));
	}
	static Matrix4X4 ProjectionMatrix(const float& fov, const float& aspect, const float& Near, const float& Far) 
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
	 static Matrix4X4 OrthoGraphicMatrix(float top, float bot, float right, float left, float Near, float Far)
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
	  static Matrix4X4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up) 
	{
		Vector3 zaxis = (at - eye).Normalize();
		Vector3 xaxis = Vector3::CrossProduct(up, zaxis).Normalize();
		Vector3 yaxis = Vector3::CrossProduct(zaxis, xaxis);

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

		LookAtMatrix.Colums[3].x = -(Vector3::DotProduct(xaxis, eye));
		LookAtMatrix.Colums[3].y = -(Vector3::DotProduct(yaxis, eye));
		LookAtMatrix.Colums[3].z = -(Vector3::DotProduct(zaxis, eye));
		LookAtMatrix.Colums[3].w = 1;


		return LookAtMatrix;


	}


}
