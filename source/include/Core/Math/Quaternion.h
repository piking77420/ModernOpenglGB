#pragma once
#include <iostream>
#include "Vector3.h"
#include "Vector4.h"

class Matrix3X3;
class Matrix4X4;

class Quaternion
{
public:

	Vector3 imaginary;
	float w = 0.f;

	constexpr static inline Quaternion Identity()
	{
		return Quaternion(Vector3::Zero(), 1.f);
	}

	constexpr inline float NormSquare() const
	{

		return imaginary.x * imaginary.x + imaginary.y * imaginary.y + imaginary.z * imaginary.z + w * w;
	}
	inline float Norm() const
	{
		return std::sqrt(NormSquare());
	}

	inline Quaternion Normalize() const
	{
		

		if(Norm() != 0.f)
		{
			Quaternion result(*this);

			float normValue = 1.f / Norm();

			result.imaginary.x *= normValue;
			result.imaginary.y *= normValue;
			result.imaginary.z *= normValue;


			result.w *= normValue;

			return result;
		}


		return *this;
	}

	constexpr inline Quaternion Conjugate() const
	{
		return Quaternion(-imaginary,w);
	}

	Quaternion ConvertToUnitNormQuaternion() const;
	

	static inline Quaternion Invert(const Quaternion& q1) 
	{
		float absoluteValue = q1.Norm();
		absoluteValue *= absoluteValue;
		absoluteValue = 1 / absoluteValue;

		Quaternion conjugateValue = q1.Conjugate();

		float scalar = conjugateValue.w * absoluteValue;

		return Quaternion( Vector3(conjugateValue[0], conjugateValue[1], conjugateValue[2]) * absoluteValue, scalar);
	}


	inline Quaternion RotateVectorAboutAngleAndAxis(float uAngle, const Vector3& axis) const
	{
		Quaternion p(axis,0);
		Vector3 axisNormalize = axis.Normalize();

		Quaternion q(axisNormalize, uAngle);
		q = q.ConvertToUnitNormQuaternion();
		Quaternion qInverse = Quaternion::Invert(q);

		Quaternion rotatedVector = q * p * qInverse;

		return rotatedVector;

	}


	[[nodiscard]]
	static inline Quaternion Multiply(const Quaternion& Q1, const Quaternion& Q2)
	{
		Vector3 im1 = Vector3(Q1[0], Q1[1], Q1[2]);
		Vector3 im2 = Vector3(Q1[0], Q1[1], Q1[2]);


		float scalarResult = Q1.w * Q2.w - Vector3::DotProduct(im1, im2);
		Vector3 vectorResult =   (im2 * Q1.w )+ im1 * Q2.w + Vector3::CrossProduct(im1, im2);
		return Quaternion(vectorResult.x, vectorResult.y, vectorResult.z, scalarResult);

	}
	[[nodiscard]]
	static inline Quaternion LookAt(const Vector3 pos,const Vector3 at)
	{

	}

	static Matrix3X3 ToRotationMatrix3X3(const Quaternion& Q1);
	

	 static Matrix4X4 ToRotationMatrix4X4(const Quaternion& Q1);	

	

	static Quaternion EulerAngle(const Vector3& eulerAngle);
	Vector3 ToEulerAngle() const ;

	[[nodiscard]]
	constexpr float* SetPtr() { return &imaginary.x; }

	[[nodiscard]]
	constexpr const float* GetPtr()const { return &imaginary.x; }



#pragma region Operator


	inline Quaternion operator*(const Quaternion& Q1) const;
	inline void operator*=(const Quaternion& Q1);
	float operator[](int i) const;
	float& operator[](int i);

#pragma endregion
	constexpr Quaternion(const Vector4& vector) : imaginary(vector.x, vector.y, vector.z), w(vector.w)
	{
	}
	constexpr Quaternion(float _x , float _y, float _z, float _w) : imaginary(_x, _y, _z), w(_w)
	{
	}
	constexpr Quaternion(const Vector3& _imaginary,float _w) : imaginary(_imaginary), w(_w)
	{
	}

	constexpr Quaternion() = default;


private:
};

#pragma region Operator

inline Quaternion Quaternion::operator*(const Quaternion& Q1) const
{
	return Multiply(*this,Q1);
}

inline void Quaternion::operator*=(const Quaternion& Q1)
{
	*this = Multiply(*this, Q1);
}



#pragma endregion

std::ostream& operator<<(std::ostream& stream, const Quaternion& q);
