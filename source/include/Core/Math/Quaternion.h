#pragma once
#include <iostream>
#include "Mathf.h"
#include "Vector3.h"

class Quaternion
{
public:

	float scalar = 0;
	Vector3 vector = Vector3::Zero();

	constexpr inline float NormSquare() const
	{
		return scalar * scalar + vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	}
	inline float Norm() const
	{
		return std::sqrtf(scalar * scalar + vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	inline Quaternion Normalize() const
	{
		

		if(Norm() != 0.f)
		{
			Quaternion result = *this;

			float normValue = 1 / Norm();

			result.scalar *= normValue;
			result.vector *= normValue;

			return result;
		}


		return *this;
	}

	constexpr inline Quaternion Conjugate() const
	{
		return Quaternion(scalar, -vector);
	}

	Quaternion ConvertToUnitNormQuaternion() const;
	

	static inline Quaternion Invert(const Quaternion& q1) 
	{
		float absoluteValue = q1.Norm();
		absoluteValue *= absoluteValue;
		absoluteValue = 1 / absoluteValue;

		Quaternion conjugateValue = q1.Conjugate();

		float scalar = conjugateValue.scalar * absoluteValue;
		Vector3 imaginary = conjugateValue.vector * absoluteValue;

		return Quaternion(scalar, imaginary);
	}


	inline Quaternion RotateVectorAboutAngleAndAxis(float uAngle, const Vector3& axis) const
	{
		Quaternion p(0,(*this).vector);
		Vector3 axisNormalize = axis.Normalize();

		Quaternion q(uAngle, axisNormalize);
		q = q.ConvertToUnitNormQuaternion();
		Quaternion qInverse = Quaternion::Invert(q);

		Quaternion rotatedVector = q * p * qInverse;

		return rotatedVector;

	}


	[[nodiscard]]
	static inline Quaternion Multiply(const Quaternion& Q1, const Quaternion& Q2)
	{
		float scalarResult = Q1.scalar * Q2.scalar - Vector3::DotProduct(Q1.vector, Q2.vector);
		Vector3 vectorResult = Q1.scalar * Q2.vector + Q1.vector * Q1.scalar + Vector3::CrossProduct(Q1.vector, Q2.vector);
		return Quaternion(scalarResult, vectorResult);

	}
	[[nodiscard]]
	static inline Quaternion LookAt(const Vector3 pos,const Vector3 at)
	{

	}

	static Matrix3X3 ToMatrix3X3(const Quaternion& Q1) ;
	static Matrix4X4 ToMatrix4X4(const Quaternion& Q1);

	static Quaternion EulerAngle(const Vector3& eulerAngle);
	Vector3 ToEulerAngle() const ;

#pragma region Operator


	inline Quaternion operator+(const Quaternion& Q1) const;
	inline Quaternion operator-(const Quaternion& Q1) const;
	inline void operator+=(const Quaternion& Q1) ;
	inline void operator-=(const Quaternion& Q1) ;
	inline Quaternion operator*(const Quaternion& Q1) const;
	inline void operator*=(float value);
	inline Quaternion operator*(float value);

	float operator[](int i) const;
	float& operator[](int i);

#pragma endregion
	constexpr Quaternion(float _scalar,const Vector3& _vector) : scalar(_scalar), vector(_vector)
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

inline Quaternion Quaternion::operator+(const Quaternion& Q1) const
{
	return Quaternion(scalar + Q1.scalar, vector + Q1.vector);
}
inline Quaternion Quaternion::operator-(const Quaternion& Q1) const
{
	return Quaternion(scalar - Q1.scalar, vector - Q1.vector);
}
inline void Quaternion::operator+=(const Quaternion& Q1) 
{
	scalar += Q1.scalar;
	vector += Q1.vector;
}
inline void Quaternion::operator-=(const Quaternion& Q1)
{
	scalar -= Q1.scalar;
	vector -= Q1.vector;
}

inline void Quaternion::operator*=(float value)
{
	scalar *= value;
	vector *= value;
}
inline Quaternion Quaternion::operator*(float value)
{
	float scalarValue = scalar * value;
	Vector3 imaginaryValue = vector * value;
	return Quaternion(scalarValue, imaginaryValue);
}
#pragma endregion

std::ostream& operator<<(std::ostream& stream, const Quaternion& q);
