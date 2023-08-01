#include "Quaternion.h"
#include "ToolBoxMathHeaders.h"



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
	
		float angle = Math::DegreesToRadians(scalar);
		Quaternion result;


		result.vector = vector.Normalize();
		result.scalar = std::cosf(angle * 0.5);
		result.vector = result.vector * std::sinf(angle * 0.5);

		return result;
	
}

Matrix3X3 Quaternion::ToMatrix3X3(const Quaternion& Q1) 
{
	Matrix3X3 result;
	
	result[0].x = 2 * (Q1[0] * Q1[0] + Q1[1] * Q1[1]) - 1 ;
	result[0].y = 2 * (Q1[1] * Q1[2] + Q1[0] * Q1[3]);
	result[0].z = 2 * (Q1[1] * Q1[3] - Q1[0] * Q1[2]);

	result[1].x = 2 * (Q1[1] * Q1[2] - Q1[0] * Q1[3]);
	result[1].y = 2 * (Q1[0] * Q1[0] + Q1[2] * Q1[2]) - 1;
	result[1].z = 2 * (Q1[2] * Q1[3] + Q1[0] * Q1[1]);

	result[2].x = 2 * (Q1[1] * Q1[3] + Q1[0] * Q1[2]);
	result[2].y = 2 * (Q1[2] * Q1[3] - Q1[0] * Q1[1]);
	result[2].z = 2 * (Q1[0] * Q1[0] + Q1[3] * Q1[3]) - 1;

	return result;
}
Matrix4X4 Quaternion::ToMatrix4X4(const Quaternion& Q1) 
{
	Matrix4X4 result;

	
	
	float w = Q1[0];
	float x = Q1[1];
	float y = Q1[2];
	float z = Q1[3];

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




	
	result[0].x = (1 - (yy + zz));
	result[0].y = (xy + wz);
	result[0].z = (xz - wy);
	result[0].w = 0;

	result[1].x = (xy - wz);
	result[1].y = (1 - (xx + zz));
	result[1].z = (yz + wx);
	result[1].w = 0;

	result[2].x = (xz + wy);
	result[2].y = (yz - wx);
	result[2].z = (1 - (xx + yy));
	result[2].w = 0;

	result[3].x = 0;
	result[3].y = 0;
	result[3].z = 0;
	result[3].w = 1;
	
	
	
	return result;
}
Quaternion Quaternion::EulerAngle(const Vector3& eulerAngle) 
{
	Quaternion q;

	float c1 = std::cosf(eulerAngle.x * 0.5f);
	float c2 = std::cosf(eulerAngle.y * 0.5f);
	float c3 = std::cosf(eulerAngle.z * 0.5f);

	float s1 = std::sinf(eulerAngle.x * 0.5f);
	float s2 = std::sinf(eulerAngle.y * 0.5f);
	float s3 = std::sinf(eulerAngle.z * 0.5f);



	q[1] = s1 * c2 * c3 + c1 * s2 * s3;
	q[2] = c1 * s2 * c3 - s1 * c2 * s3;
	q[3] = c1 * c2 * s3 + s1 * s2 * c3;
	q[0] = c1 * c2 * c3 - s1 * s2 * s3;

	return q;
}

Vector3 Quaternion::ToEulerAngle() const
{
	float roll;
	float pitch;
	float yaw;

	roll = std::atan2f(std::sqrt(1 + 2 * (scalar * vector.y - vector.x * vector.z)), std::sqrt(1 - 2 * (scalar * vector.y - vector.x * vector.z)));

	float sinp = std::sqrt(1 + 2 * (scalar * vector.y - vector.x * vector.z));
	float cosp = std::sqrt(1 + 2 * (scalar * vector.y - vector.x * vector.z));
	pitch = 2 * std::atan2(sinp, cosp) - M_PI / 2;

	float sinycosp = 2 * (scalar * vector.z + vector.x * vector.y);
	float cosycosp = 1 - 2 * (vector.y * vector.y + vector.z * vector.z);

	yaw = std::atan2(sinycosp, cosycosp);

	return Vector3(roll,pitch,yaw);
}


std::ostream& operator<<(std::ostream& stream, const Quaternion& q)
{
	
	stream << "scalar " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << '\n';


	return stream;
}
