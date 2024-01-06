#include "Quaternion.h"
#include "ToolBoxMathHeaders.h"

#include "Matrix4X4.h"
#include "Matrix3X3.h"

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



Matrix3X3 Quaternion::ToRotationMatrix3X3(const Quaternion& Q1)
{
	float b = Q1[0];
	float c = Q1[1];
	float d = Q1[2];
	float a = Q1[3];

	float aa = a * a;
	float bb = b * b;
	float cc = c * c;
	float dd = d * d;

	float bc = b * c;
	float da = d * a;
	float bd = b * d;
	float ca = c * a;
	float ba = b * a;
	float cd = c * d;

	return {
				{2.f * (aa + bb) - 1.f,2.f * (bc + da), 2.f * (bd - ca)},
				{2.f * (bc - da), 2.f * (aa + cc) - 1.f, 2.f * (cd + ba) },
				{2.f * (bd + ca),2.f * (cd - ba),2.f * (aa + dd) - 1.f},
	};
}

Matrix4X4 Quaternion::ToRotationMatrix4X4(const Quaternion& Q1)
{
	float b = Q1[0];
	float c = Q1[1];
	float d = Q1[2];
	float a = Q1[3];

	float aa = a * a;
	float bb = b * b;
	float cc = c * c;
	float dd = d * d;

	float bc = b * c;
	float da = d * a;
	float bd = b * d;
	float ca = c * a;
	float ba = b * a;
	float cd = c * d;

	return {
				{2.f * (aa + bb) - 1.f,2.f * (bc + da), 2.f * (bd - ca),0.f},
				{2.f * (bc - da), 2.f * (aa + cc) - 1.f, 2.f * (cd + ba),0.f },
				{2.f * (bd + ca),2.f * (cd - ba),2.f * (aa + dd) - 1.f,0.f},
				{0.f, 0.f,0.f, 1.f}
	};
}

Quaternion Quaternion::FromMatrix(const Matrix4X4& matrix)
{
	Matrix3X3 m = Matrix3X3(static_cast<Vector3>(matrix[0]), static_cast<Vector3>(matrix[1]), static_cast<Vector3>(matrix[2]));

	float trace = m.Trace();

	float a = sqrtf(1.f + trace) / 2.f;
	float divide = 4.f * a;
	float b = m[2][1] - m[1][2];
	float c = m[0][2] - m[2][0];
	float d = m[1][0] - m[0][1];

	float denom = 1.f / divide;

	return Quaternion(b * denom, c * denom, d * denom, -a).Normalize();
}

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
		v.x = (float)M_PI / 2.f;
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

	Quaternion rot = Quaternion(imaginary.z, imaginary.x, imaginary.y, w);
	v.y = std::atan2(2.f * rot.imaginary.x * rot.w + 2.f * rot.imaginary.y * rot.imaginary.z, 1 - 2.f * (rot.imaginary.z * rot.imaginary.z + rot.w * rot.w));     // Yaw
	v.x = std::asin(2.f * (rot.imaginary.x * rot.imaginary.z - rot.w * rot.imaginary.y));                             // Pitch
	v.z = std::atan2(2.f * rot.imaginary.x * rot.imaginary.y + 2.f * rot.imaginary.z * rot.w, 1 - 2.f * (rot.imaginary.y * rot.imaginary.y + rot.imaginary.z * rot.imaginary.z));      // Roll
	return NormalizeAngles(v);
}

//Not the shortest way for now
Quaternion Quaternion::Nlerp(Quaternion start, Quaternion end, float percent)
{
	Quaternion lerped = Math::Lerp(start, end, percent).Normalize();

	//Always take the shortest way DOESN'T WORK RN
	if (lerped.w > M_PI - Math::Epsilon())
	{
		lerped = lerped.Conjugate();
	}

	return lerped;
}

std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{
	stream << " i " << q[0] << " j " << q[1] << " k  " << q[2] << " w " << q[3] << '\n';

	return stream;
}
