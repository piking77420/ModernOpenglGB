#include "Quaternion.h"


Quaternion::Quaternion(float _scalar, const Vector3& _vector) : scalar(_scalar) , vector(_vector)
{
}

Quaternion::Quaternion()
{
}

Quaternion::~Quaternion()
{
}
float Quaternion::operator[](int i) const
{
	assert(i >= 0 && i < 4);
	const float* data = &scalar;
	return data[i];
}

float& Quaternion::operator[](int i)
{
	assert(i >= 0 && i < 4);
	float* data = &scalar;
	return data[i];
}


Quaternion Quaternion::ConvertToUnitNormQuaternion() const
{
	{
		float angle = Math::DegreesToRadians(scalar);
		Quaternion result;


		result.vector = vector.Normalize();
		result.scalar = std::cosf(angle * 0.5);
		result.vector = result.vector * std::sinf(angle * 0.5);

		return result;
	}
}

Matrix4X4 Quaternion::ToMatrix(const Quaternion& Q1) const
{
	Matrix4X4 result;
	
	result[0].x = 2 * (Q1.scalar * Q1.scalar + Q1.vector.x * Q1.vector.x) - 1 ;
	result[0].y = 2 * (Q1.vector.x * Q1.vector.y + Q1.scalar * Q1.vector.z);
	result[0].z = 2 * (Q1.vector.x * Q1.vector.z - Q1.scalar * Q1.vector.y);
	result[0].w = 0;

	result[1].x = 2 * (Q1.vector.x * Q1.vector.y - Q1.scalar * Q1.vector.z);
	result[1].y = 2 * (Q1.scalar * Q1.scalar + Q1.vector.y * Q1.vector.y) - 1;
	result[1].z = 2 * (Q1.vector.y * Q1.vector.z + Q1.scalar * Q1.vector.x);
	result[1].w = 0;

	result[2].x = 2 * (Q1.vector.x * Q1.vector.z + Q1.scalar * Q1.vector.y);
	result[2].y = 2 * (Q1.vector.y * Q1.vector.z - Q1.scalar * Q1.vector.x);
	result[2].z = 2 * (Q1.scalar * Q1.scalar + Q1.vector.z * Q1.vector.z) - 1;
	result[2].w = 0;

	result[3].x = 0;
	result[3].y = 0;
	result[3].z = 0;
	result[3].w = 1;

	return result;
}
Quaternion Quaternion::EulerAngle(const Vector3& eulerAngle) const
{
	Quaternion q;

	float cr = std::cos(eulerAngle.x * 0.5);
	float sr = std::sin(eulerAngle.x * 0.5);
	float cp = std::cos(eulerAngle.y * 0.5);
	float sp = std::sin(eulerAngle.y * 0.5);
	float cy = std::cos(eulerAngle.z * 0.5);
	float sy = std::sin(eulerAngle.z * 0.5);

	q.scalar = sr * cp * cy - cr * sp * sy;
	q.vector.z = cr * cp * cy + sr * sp * sy;
	q.vector.x = cr * sp * cy + sr * cp * sy;
	q.vector.y = cr * cp * sy - sr * sp * cy;

	return q;
}


std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{
	stream << "Scalar : " << q.scalar << " " << "Imaginary part : " << "i:" << q.vector.x << " j:" << q.vector.y << " k:" << q.vector.z;
	stream << '\n';
	return stream;
}
