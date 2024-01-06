#pragma once
#include <iostream>
#include "Vector3.h"
#include "Vector4.h"

class Matrix3X3;
class Matrix4X4;

class Quaternion
{
public:

	Vector3 imaginary = Vector3::Zero();
	float w = 1.f;

	constexpr static inline Quaternion Identity()
	{
		return Quaternion(Vector3::Zero(), 1.f);
	}
	static constexpr float DotProduct(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.imaginary.x * q2.imaginary.x + q1.imaginary.y * q2.imaginary.y + q1.imaginary.z * q2.imaginary.z + q1.w * q2.w;
	}

	constexpr inline float NormSquare() const
	{
		return DotProduct(*this, *this);
	}
	inline float Norm() const
	{
		return std::sqrt(NormSquare());
	}


	// in radians
	static Quaternion AngleAxis(float angle , const Vector3& axis) 
	{
		float Qangle = angle / 2.f;
		Vector3 axisN = axis.Normalize();
		return Quaternion(std::sin(Qangle) * axisN.x, std::sin(Qangle) * axisN.y, std::sin(Qangle) * axisN.z, std::cos(Qangle));
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

	Quaternion inline ReturnToUnitNormQuaternion() const 
	{
		Quaternion result;
		float angle = w;
		result.imaginary = imaginary.Normalize();
		result.w = std::cosf(angle * 0.5f);
		result.imaginary = result.imaginary * std::sinf(angle * 0.5f);

		return result;
	}
	

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
		q = q.ReturnToUnitNormQuaternion();
		Quaternion qInverse = Quaternion::Invert(q);

		Quaternion rotatedVector = q * p * qInverse;

		return rotatedVector;
	}


	[[nodiscard]]
	static inline Quaternion Multiply(const Quaternion& Q1, const Quaternion& Q2)
	{
		Vector3 im1 = Vector3(Q1[0], Q1[1], Q1[2]);
		Vector3 im2 = Vector3(Q2[0], Q2[1], Q2[2]);


		float scalarResult = Q1.w * Q2.w - Vector3::DotProduct(im1, im2);
		Vector3 vectorResult =   (im2 * Q1.w )+ (im1 * Q2.w) + Vector3::CrossProduct(im1, im2);
		return Quaternion(vectorResult.x, vectorResult.y, vectorResult.z, scalarResult);
	}
	[[nodiscard]]
	static inline Quaternion LookAt(const Vector3 SourcePoint,const Vector3 At)
	{
		Vector3 forwardVector = Vector3(At - SourcePoint);

		float dot = Vector3::DotProduct(Vector3::Forward(), forwardVector);

		if (std::abs(dot - (-1.0f)) < 0.000001f)
		{
			return Quaternion(Vector3::Up(), (float)M_PI);
		}
		if (std::abs(dot - (1.0f)) < 0.000001f)
		{
			return Quaternion::Identity();
		}

		float rotAngle = std::acos(dot);
		Vector3 rotAxis = Vector3::CrossProduct(Vector3::Forward(), forwardVector).Normalize();
		return AngleAxis(rotAngle, rotAxis);
	}

	static Matrix3X3 ToRotationMatrix3X3(const Quaternion& Q1);
	

	static Matrix4X4 ToRotationMatrix4X4(const Quaternion& Q1);

	
	static Quaternion FromMatrix(const Matrix4X4& matrix);


	static inline Quaternion FromEulerAngle(const Vector3& eulerAngle)
	{
		Quaternion q;
		Vector3 c = Vector3(std::cos(eulerAngle.x * 0.5f), std::cos(eulerAngle.y * 0.5f), std::cos(eulerAngle.z * 0.5f));
		Vector3 s = Vector3(std::sin(eulerAngle.x * 0.5f), std::sin(eulerAngle.y * 0.5f), std::sin(eulerAngle.z * 0.5f));

		q.imaginary.x = s.x * c.y * c.z + c.x * s.y * s.z;
		q.imaginary.y = c.x * s.y * c.z - s.x * c.y * s.z;
		q.imaginary.z = c.x * c.y * s.z + s.x * s.y * c.z;
		q.w = c.x * c.y * c.z - s.x * s.y * s.z;

		return q;
	}

	// https://forum.unity.com/threads/is-there-a-conversion-method-from-quaternion-to-euler.624007/
	Vector3 ToEulerAngle() const;
	


	[[nodiscard]] static inline Quaternion Slerp(const Quaternion& t1, const Quaternion& t2, float t)
	{
		float cosOmega = DotProduct(t1, t2);
		
		bool flip = false;

		if (cosOmega < -Math::Epsilon())
		{
			flip = true;
			cosOmega = -cosOmega;
		}

		float s1, s2;

		if (cosOmega > (1.0f - Math::Epsilon()))
		{
			// Too close, do straight linear interpolation.
			s1 = 1.0f - t;
			s2 = (flip) ? -t : t;
		}
		else
		{
			float omega = std::cos(cosOmega);
			float invSinOmega = 1.f / std::sin(omega);

			s1 = std::sin((1.0f - t) * omega) * invSinOmega;
			s2 = (flip)
				? -std::sin(t * omega) * invSinOmega
				: std::sin(t * omega) * invSinOmega;
		}

		Quaternion ans;

		ans.imaginary.x = s1 * t1.imaginary.x + s2 * t2.imaginary.x;
		ans.imaginary.y = s1 * t1.imaginary.y + s2 * t2.imaginary.y;
		ans.imaginary.z = s1 * t1.imaginary.z + s2 * t2.imaginary.z;
		ans.w = s1 * t1.w + s2 * t2.w;

		return ans;
	}


	static Quaternion Nlerp(Quaternion start, Quaternion end, float percent);


	[[nodiscard]]
	constexpr float* SetPtr() { return &imaginary.x; }

	[[nodiscard]]
	constexpr const float* GetPtr()const { return &imaginary.x; }
		

#pragma region Operator


	inline Quaternion operator*(const Quaternion& Q1) const
	{
		return Multiply(*this, Q1);
	}

	inline void operator*=(const Quaternion& Q1)
	{
		*this = Multiply(*this, Q1);
	}

	inline Quaternion operator*(float value) const
	{
		return { imaginary.x * value , imaginary.y * value ,imaginary.z * value ,w * value };
	}

	inline Quaternion operator+(const Quaternion& q) const
	{
		return { imaginary.x + q.imaginary.x , imaginary.y + q.imaginary.y ,imaginary.z + q.imaginary.z ,w + q.w };
	}


	float operator[](int i) const
	{
		assert(i >= 0 && i < 4);
		const float* data = &imaginary.x;
		return data[i];
	}

	float& operator[](int i)
	{
		assert(i >= 0 && i < 4);
		float* data = &imaginary.x;
		return data[i];
	}


#pragma endregion
#pragma region Constructor

	constexpr Quaternion(const Vector4& vector) : imaginary(vector.x, vector.y, vector.z), w(vector.w)
	{
	}
	constexpr Quaternion(float _x , float _y, float _z, float _w) : imaginary(_x, _y, _z), w(_w)
	{
	}
	constexpr Quaternion(const Vector3& _imaginary,float _w) : imaginary(_imaginary), w(_w)
	{
	}
	// From Vector angle
	Quaternion(const Vector3& _Vector)
	{
		*this = Quaternion::FromEulerAngle(_Vector * Math::Deg2Rad);
	}

	constexpr Quaternion() = default;

#pragma endregion


private:
};


std::ostream& operator<<(std::ostream& stream, const Quaternion& q);
