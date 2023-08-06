#include "Quaternion.h"
#include "ToolBoxMathHeaders.h"

#include "Matrix4X4.h"
#include "Matrix3X3.h"

float Quaternion::operator[](int i) const
{
	assert(i >= 0 && i < 4);
	const float* data = &imaginary.x;
	return data[i];
}

float& Quaternion::operator[](int i)
{
	assert(i >= 0 && i < 4);
	float* data = &imaginary.x;
	return data[i];
}


Quaternion Quaternion::ConvertToUnitNormQuaternion() const
{
	

	float angle = Math::DegreesToRadians(w);
	Quaternion result;


	result.imaginary = imaginary.Normalize();
	result.w = std::cosf(angle * 0.5);
	result.imaginary = result.imaginary * std::sinf(angle * 0.5);

	return result;

	
}


Matrix3X3 Quaternion::ToRotationMatrix3X3(const Quaternion& Q1)
{

	float x = Q1[0];
	float y = Q1[1];
	float z = Q1[2];
	float w = Q1[3];

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	float xx = x * x2;
	float xy = x * y2;
	float xz = x * z2;
	float yy = y * y2;
	float yz = y * z2;
	float zz = z * z2;
	float wx = w * x2;
	float wy = w * y2;
	float wz = w * z2;

	return {
				{(1 - (yy + zz)),(xy + wz), (xz - wy) },
				{(xy - wz), (1 - (xx + zz)),(yz + wx) },
				{(xz + wy), (yz - wx),(1 - (xx + yy))},
	};
}

Matrix4X4 Quaternion::ToRotationMatrix4X4(const Quaternion& Q1)
{
	

	float x = Q1[0];
	float y = Q1[1];
	float z = Q1[2];
	float w = Q1[3];

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	float xx = x * x2;
	float xy = x * y2;
	float xz = x * z2;
	float yy = y * y2;
	float yz = y * z2;
	float zz = z * z2;
	float wx = w * x2;
	float wy = w * y2;
	float wz = w * z2;


	return {
				{(1 - (yy + zz)),(xy + wz), (xz - wy),0.f },
				{(xy - wz), (1 - (xx + zz)),(yz + wx),0.f },
				{(xz + wy), (yz - wx),(1 - (xx + yy)),0},
				{0, 0,0, 1.f}
	};
	
	
}

Quaternion Quaternion::EulerAngle(const Vector3& eulerAngle)
{
	Quaternion q;

	float c1 = std::cos(eulerAngle.x * 0.5f);
	float c2 = std::cos(eulerAngle.y * 0.5f);
	float c3 = std::cos(eulerAngle.z * 0.5f);

	float s1 = std::sin(eulerAngle.x * 0.5f);
	float s2 = std::sin(eulerAngle.y * 0.5f);
	float s3 = std::sin(eulerAngle.z * 0.5f);



	q[0] = s1 * c2 * c3 + c1 * s2 * s3;
	q[1] = c1 * s2 * c3 - s1 * c2 * s3;
	q[2] = c1 * c2 * s3 + s1 * s2 * c3;
	q[3] = c1 * c2 * c3 - s1 * s2 * s3;

	return q;
}


//Quaternion to Euler angles(in 3 - 2 - 1 sequence) conversion
Vector3 Quaternion::ToEulerAngle() const
{
	Quaternion qNorm = this->Normalize();


	float x = qNorm.imaginary.x;
	float y = qNorm.imaginary.y;
	float z = qNorm.imaginary.z;

	float roll = 0.f;
	float pitch = 0.f;
	float yaw = 0.f;

	float sinr = 2.f * (w * x + y * z);
	float cosr = 1.f - 2.f * (x * x + y * y);
	roll = std::atan2(sinr, cosr);

	// pitch (y-axis rotation)
	float sinp = 2 * (w * y - x * z);
	float cosp = 1 - 2 * (w * w + x * x);
	pitch = std::atan2(sinp, cosp);


	// yaw (z-axis rotation)
	float siny = 2.f * (w * z + x * y);
	float cosy = 1.f - 2.f * (y * y + z * z);
	yaw = std::atan2(siny, cosy);


	return Vector3(roll,pitch,yaw);
}


std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{
	
	stream << " i " << q[0] << " j " << q[1] << " k  " << q[2] << " w " << q[3] << '\n';


	return stream;
}
