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


	float angle = w;
	Quaternion result;


	result.imaginary = imaginary.Normalize();
	result.w = std::cosf(angle * 0.5f);
	result.imaginary = result.imaginary * std::sinf(angle * 0.5f);

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
	Vector3 c = Vector3(std::cos(eulerAngle.x * 0.5f), std::cos(eulerAngle.y * 0.5f), std::cos(eulerAngle.z * 0.5f));
	Vector3 s = Vector3(std::sin(eulerAngle.x * 0.5f), std::sin(eulerAngle.y * 0.5f), std::sin(eulerAngle.z * 0.5f));

	q.w = c.x * c.y * c.z + s.x * s.y * s.z;
	q.imaginary.x = s.x * c.y * c.z - c.x * s.y * s.z;
	q.imaginary.y = c.x * s.y * c.z + s.x * c.y * s.z;
	q.imaginary.z = c.x * c.y * s.z - s.x * s.y * c.z;

	return q;
}

float NormalizeAngle(float angle)
{
	while (angle > (float)M_PI * 2.f)
		angle -= (float)M_PI * 2.f;
	while (angle < 0)
		angle += (float)M_PI * 2.f;
	return angle;
}
Vector3 NormalizeAngles(Vector3 angles)
{
	angles.x = NormalizeAngle(angles.x);
	angles.y = NormalizeAngle(angles.y);
	angles.z = NormalizeAngle(angles.z);
	return angles;
}


// https://forum.unity.com/threads/is-there-a-conversion-method-from-quaternion-to-euler.624007/
Vector3 Quaternion::ToEulerAngle() const
{

	float sqw = w * w;
	float sqx = imaginary.x * imaginary.x;
	float sqy = imaginary.y * imaginary.y;
	float sqz = imaginary.z * imaginary.z;
	float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	float test = imaginary.x * w - imaginary.y * imaginary.z;
	Vector3 v;

	if (test > 0.4995f * unit)
	{ // singularity at north pole
		v.y = 2.f * std::atan2(imaginary.y, imaginary.x);
		v.x = (float)M_PI/ 2.f;
		v.z = 0;
		return NormalizeAngles(v);
	}
	if (test < -0.4995f * unit)
	{ // singularity at south pole
		v.y = -2.f * std::atan2(imaginary.y, imaginary.x);
		v.x = -(float)M_PI / 2.f;
		v.z = 0.f;
		return NormalizeAngles(v);
	}

	Quaternion rot = Quaternion( imaginary.z, imaginary.x, imaginary.y ,w);
	v.y = std::atan2(2.f * rot.imaginary.x * rot.w + 2.f * rot.imaginary.y * rot.imaginary.z, 1 - 2.f * (rot.imaginary.z * rot.imaginary.z + rot.w * rot.w));     // Yaw
	v.x = std::asin(2.f * (rot.imaginary.x * rot.imaginary.z - rot.w * rot.imaginary.y));                             // Pitch
	v.z = std::atan2(2.f * rot.imaginary.x * rot.imaginary.y + 2.f * rot.imaginary.z * rot.w, 1 - 2.f * (rot.imaginary.y * rot.imaginary.y + rot.imaginary.z * rot.imaginary.z));      // Roll
	return NormalizeAngles(v);


}


std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{

	stream << " i " << q[0] << " j " << q[1] << " k  " << q[2] << " w " << q[3] << '\n';


	return stream;
}
