#include "Matrix4X4.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Vector.h"









inline Vector3 Matrix4X4::GetPos()
{
	return static_cast<Vector3>(Colums[3]);
}



Matrix4X4 Matrix4X4::RotationX4X4(const float& angle)
{
	Matrix4X4 result;
	
	result.Colums[0].x = 1;
	result.Colums[0].y = 0;
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = std::cos((angle));
	result.Colums[1].z = std::sin((angle));
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = -std::sin((angle));
	result.Colums[2].z = std::cos((angle));
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	

	return result;

}

Matrix4X4 Matrix4X4::RotationMatrix4X4(const Vector3& angle)
{
	Matrix4X4 result;
	result = RotationZ4X4(angle.z) * RotationY4X4(angle.y) * RotationX4X4(angle.x);

	return result;
}







// rad
Matrix4X4 Matrix4X4::RotationY4X4(const float& angle)
{
	Matrix4X4 result;
	

	result.Colums[0].x = std::cos((angle));
	result.Colums[0].y = 0;
	result.Colums[0].z = -std::sin((angle));
	result.Colums[0].w = 0;

	result.Colums[1].x = 0;
	result.Colums[1].y = 1;
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = std::sin((angle));
	result.Colums[2].y = 0;
	result.Colums[2].z = std::cos((angle));
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	
	return result;
}

// rad
Matrix4X4 Matrix4X4::RotationZ4X4(const float& angle)
{
	Matrix4X4 result;
	



	result.Colums[0].x = std::cos((angle));
	result.Colums[0].y = std::sin((angle));
	result.Colums[0].z = 0;
	result.Colums[0].w = 0;

	result.Colums[1].x = -std::sin((angle));
	result.Colums[1].y = std::cos((angle));
	result.Colums[1].z = 0;
	result.Colums[1].w = 0;

	result.Colums[2].x = 0;
	result.Colums[2].y = 0;
	result.Colums[2].z = 1;
	result.Colums[2].w = 0;

	result.Colums[3].x = 0;
	result.Colums[3].y = 0;
	result.Colums[3].z = 0;
	result.Colums[3].w = 1;
	
	return result;
}

inline Matrix4X4 Matrix4X4::AdjoinMatrix(const Matrix4X4& matrix)
{

	Matrix4X4 copy = matrix.Transposate();
	Matrix4X4 minor;

	Matrix3X3 m1 = Matrix3X3(Vector3(copy[1][1], copy[1][2], copy[1][3]), Vector3(copy[2][1], copy[2][2], copy[2][3]), Vector3(copy[3][1], copy[3][2], copy[3][3]));
	minor[0][0] = Matrix3X3::Determinant(m1);

	Matrix3X3 m2 = Matrix3X3(Vector3(copy[1][0], copy[1][2], copy[1][3]), Vector3(copy[2][0], copy[2][2], copy[2][3]), Vector3(copy[3][0], copy[3][2], copy[3][3]));
	minor[0][1] = -Matrix3X3::Determinant(m2);

	Matrix3X3 m3 = Matrix3X3(Vector3(copy[1][0], copy[1][1], copy[1][3]), Vector3(copy[2][0], copy[2][1], copy[2][3]), Vector3(copy[3][0], copy[3][1], copy[3][3]));
	minor[0][2] = Matrix3X3::Determinant(m3);

	Matrix3X3 m4 = Matrix3X3(Vector3(copy[1][0], copy[1][1], copy[1][2]), Vector3(copy[2][0], copy[2][1], copy[2][2]), Vector3(copy[3][0], copy[3][1], copy[3][2]));
	minor[0][3] = -Matrix3X3::Determinant(m4);



	m1 = Matrix3X3(Vector3(copy[0][1], copy[0][2], copy[0][3]), Vector3(copy[2][1], copy[2][2], copy[2][3]), Vector3(copy[3][1], copy[3][2], copy[3][3]));
	minor[1][0] = -Matrix3X3::Determinant(m1);

	m2 = Matrix3X3(Vector3(copy[0][0], copy[0][2], copy[0][3]), Vector3(copy[2][0], copy[2][2], copy[2][3]), Vector3(copy[3][0], copy[3][2], copy[3][3]));
	minor[1][1] = Matrix3X3::Determinant(m2);

	m3 = Matrix3X3(Vector3(copy[0][0], copy[0][1], copy[0][3]), Vector3(copy[2][0], copy[2][1], copy[2][3]), Vector3(copy[3][0], copy[3][1], copy[3][3]));
	minor[1][2] = -Matrix3X3::Determinant(m3);

	m4 = Matrix3X3(Vector3(copy[0][0], copy[0][1], copy[0][2]), Vector3(copy[2][0], copy[2][1], copy[2][2]), Vector3(copy[3][0], copy[3][1], copy[3][2]));
	minor[1][3] = Matrix3X3::Determinant(m4);



	m1 = Matrix3X3(Vector3(copy[0][1], copy[0][2], copy[0][3]), Vector3(copy[1][1], copy[1][2], copy[1][3]), Vector3(copy[3][1], copy[3][2], copy[3][3]));
	minor[2][0] = Matrix3X3::Determinant(m1);

	m2 = Matrix3X3(Vector3(copy[0][0], copy[0][2], copy[0][3]), Vector3(copy[1][0], copy[1][2], copy[1][3]), Vector3(copy[3][0], copy[3][2], copy[3][3]));
	minor[2][1] = -Matrix3X3::Determinant(m2);

	m3 = Matrix3X3(Vector3(copy[0][0], copy[0][1], copy[0][3]), Vector3(copy[1][0], copy[1][1], copy[1][3]), Vector3(copy[3][0], copy[3][1], copy[3][3]));
	minor[2][2] = Matrix3X3::Determinant(m3);

	m4 = Matrix3X3(Vector3(copy[0][0], copy[0][1], copy[0][2]), Vector3(copy[1][0], copy[1][1], copy[1][2]), Vector3(copy[3][0], copy[3][1], copy[3][2]));
	minor[2][3] = -Matrix3X3::Determinant(m4);




	m1 = Matrix3X3(Vector3(copy[0][1], copy[0][2], copy[0][3]), Vector3(copy[1][1], copy[1][2], copy[1][3]), Vector3(copy[2][1], copy[2][2], copy[2][3]));
	minor[3][0] = -Matrix3X3::Determinant(m1);

	m2 = Matrix3X3(Vector3(copy[0][0], copy[0][2], copy[0][3]), Vector3(copy[1][0], copy[1][2], copy[1][3]), Vector3(copy[2][0], copy[2][2], copy[2][3]));
	minor[3][1] = Matrix3X3::Determinant(m2);

	m3 = Matrix3X3(Vector3(copy[0][0], copy[0][1], copy[0][3]), Vector3(copy[1][0], copy[1][1], copy[1][3]), Vector3(copy[2][0], copy[2][1], copy[2][3]));
	minor[3][2] = -Matrix3X3::Determinant(m3);

	m4 = Matrix3X3(Vector3(copy[0][0], copy[0][1], copy[0][2]), Vector3(copy[1][0], copy[1][1], copy[1][2]), Vector3(copy[2][0], copy[2][1], copy[2][2]));
	minor[3][3] = Matrix3X3::Determinant(m4);


	return minor;
}






Matrix4X4 Matrix4X4::Invert()  
{
	Matrix4X4 adj = Matrix4X4::AdjoinMatrix(*this);
	float determinant = Determinant(*this);

	Matrix4X4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			result[i][k] = (1 / determinant) * adj[i][k];
		}
	}

	return result;
}





inline float Matrix4X4::Determinant(const Matrix4X4& matrix)
{
	float result = 0;

	Matrix3X3 m0;
	m0.Coloms[0].x = matrix.Colums[1].y; m0.Coloms[1].x = matrix.Colums[2].y; m0.Coloms[2].x = matrix.Colums[3].y;
	m0.Coloms[0].y = matrix.Colums[1].z; m0.Coloms[1].y = matrix.Colums[2].z; m0.Coloms[2].y = matrix.Colums[3].z;
	m0.Coloms[0].z = matrix.Colums[1].w; m0.Coloms[1].z = matrix.Colums[2].w; m0.Coloms[2].z = matrix.Colums[3].w;


	Matrix3X3 m1;
	m1.Coloms[0].x = matrix.Colums[1].x; m1.Coloms[1].x = matrix.Colums[2].x; m1.Coloms[2].x = matrix.Colums[3].x;
	m1.Coloms[0].y = matrix.Colums[1].z; m1.Coloms[1].y = matrix.Colums[2].z; m1.Coloms[2].y = matrix.Colums[3].z;
	m1.Coloms[0].z = matrix.Colums[1].w; m1.Coloms[1].z = matrix.Colums[2].w; m1.Coloms[2].z = matrix.Colums[3].w;


	Matrix3X3 m2;
	m2.Coloms[0].x = matrix.Colums[1].x; m2.Coloms[1].x = matrix.Colums[2].x; m2.Coloms[2].x = matrix.Colums[3].x;
	m2.Coloms[0].y = matrix.Colums[1].y; m2.Coloms[1].y = matrix.Colums[2].y; m2.Coloms[2].y = matrix.Colums[3].y;
	m2.Coloms[0].z = matrix.Colums[1].w; m2.Coloms[1].z = matrix.Colums[2].w; m2.Coloms[2].z = matrix.Colums[3].w;

	Matrix3X3 m3;
	m3.Coloms[0].x = matrix.Colums[1].x; m3.Coloms[1].x = matrix.Colums[2].x; m3.Coloms[2].x = matrix.Colums[3].x;
	m3.Coloms[0].y = matrix.Colums[1].y; m3.Coloms[1].y = matrix.Colums[2].y; m3.Coloms[2].y = matrix.Colums[3].y;
	m3.Coloms[0].z = matrix.Colums[1].z; m3.Coloms[1].z = matrix.Colums[2].z; m3.Coloms[2].z = matrix.Colums[3].z;



	float add0 = matrix.Colums[0].x * Matrix3X3::Determinant(m0);
	float add1 = -1.f * matrix.Colums[0].y * Matrix3X3::Determinant(m1);
	float add2 = matrix.Colums[0].z * Matrix3X3::Determinant(m2);
	float add3 = -1.f * matrix.Colums[0].w * Matrix3X3::Determinant(m3);


	result = add0 + add1 + add2 + add3;
	
	return result;
}











Matrix4X4::operator Matrix()
{
	Matrix result = Matrix(4);


	for (size_t i = 0; i < 4; i++)
	{
		for (size_t y = 0; y < 4; y++)
		{
			result[i][y] = Colums[i][y];

		}
	}

	return result;
}










 Vector4 operator*( Matrix4X4& matrix, const Vector4& Row1)
{
		

	 Vector4 newVec;



	 newVec.x = (Row1.x * matrix[0].x) + (Row1.y * matrix[0].y) + (Row1.z * matrix[0].z) + (Row1.w * matrix[0].w);

	 newVec.y = (Row1.x * matrix[1].x) + (Row1.y * matrix[1].y) + (Row1.z * matrix[1].z) + (Row1.w * matrix[1].w);

	 newVec.z = (Row1.x * matrix[2].x) + (Row1.y * matrix[2].y) + (Row1.z * matrix[2].z) + (Row1.w * matrix[2].w);

	 newVec.w = (Row1.x * matrix[3].x) + (Row1.y * matrix[3].y) + (Row1.z * matrix[3].z) + (Row1.w * matrix[3].w);



	 return newVec;
	
}

 Vector4 operator*(const Vector4& Row1, const Matrix4X4& matrix)
 {
		 Vector4 newVec;

		 newVec.x = (Row1.x * matrix[0].x) + (Row1.y * matrix[0].y)  +( Row1.z * matrix[0].z)  +( Row1.w * matrix[0].w);

		 newVec.y = (Row1.x * matrix[1].x) + (Row1.y * matrix[1].y)  +(Row1.z * matrix[1].z)  +(Row1.w * matrix[1].w);

		 newVec.z = (Row1.x * matrix[2].x) + (Row1.y * matrix[2].y)  +(Row1.z * matrix[2].z)  +(Row1.w * matrix[2].w);

		 newVec.w = (Row1.x * matrix[3].x) + (Row1.y * matrix[3].y)  +(Row1.z * matrix[3].z)  +(Row1.w * matrix[3].w);



		 return newVec;
 }
 
std::ostream& operator<<(std::ostream& stream, const Matrix4X4& maxtrix)
{

	for (short int i = 0; i < 4; i++)
	{
		for (short int k = 0;k < 4;k++)
		{
			float value = maxtrix.Colums[k][i];
			if (value > -0.0002 && value < 0.0002)
				value = 0;

			stream << value << " ";
		}
		stream << '\n';
	}
	/*
	stream << maxtrix.Colums[0].x << " " << maxtrix.Colums[1].x << " " << maxtrix.Colums[2].x << " " << maxtrix.Colums[3].x << " ";
	stream << '\n';
	stream << maxtrix.Colums[0].y << " " << maxtrix.Colums[1].y << " " << maxtrix.Colums[2].y << " " << maxtrix.Colums[3].y << " ";
	stream << '\n';
	stream << maxtrix.Colums[0].z << " " << maxtrix.Colums[1].z << " " << maxtrix.Colums[2].z << " " << maxtrix.Colums[3].z << " ";
	stream << '\n';
	stream << maxtrix.Colums[0].w << " " << maxtrix.Colums[1].w << " " << maxtrix.Colums[2].w << " " << maxtrix.Colums[3].w << " ";
	*/
	return stream;
}