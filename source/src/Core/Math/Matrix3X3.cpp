#include "Matrix3X3.h"
#include "Vector2.h"
#include "Matrix.h"


Matrix3X3 Matrix3X3::TranslationMatrix3X3(const Vector2& translation)
{
	Matrix3X3 result;

	result.Coloms[0].x = translation.x;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = translation.y;
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;


	return result;
}

Matrix3X3 Matrix3X3::Rotation2DMatrix3X3(const float& angle)
{
	Matrix3X3 result;

	result.Coloms[0].x = std::cos((angle));
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = std::sin((angle));
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;

	return result;

}



Matrix3X3 Matrix3X3::Identity() 
{
	Matrix3X3 result;

	result.Coloms[0].x = 1;
	result.Coloms[0].y = 0;
	result.Coloms[0].z = 0;


	result.Coloms[1].x = 0;
	result.Coloms[1].y = 1;
	result.Coloms[1].z = 0;



	result.Coloms[2].x = 0;
	result.Coloms[2].y = 0;
	result.Coloms[2].z = 1;


	return result;
}





Matrix3X3 Matrix3X3::Invert()
{/*
	Matrix m = (Matrix)*this;

	m = m.Invert();

	return (Matrix3X3)m;*/

	Matrix3X3 adj = Matrix3X3::AdjoinMatrix(*this);
	float determinant = Matrix3X3::Determinant(*this);

	Matrix3X3 result;
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			result[i][k] = (1 / determinant) * adj[i][k];
		}
	}

	return result;
}








Matrix3X3::operator Matrix()
{
	Matrix result = Matrix(3); 

	result[0][0] = Coloms[0].x;
	result[1][0] = Coloms[0].y;
	result[2][0] = Coloms[0].z;

	result[0][1] = Coloms[1].x;
	result[1][1] = Coloms[1].y;
	result[2][1] = Coloms[1].z;


	result[0][2] = Coloms[2].x;
	result[1][2] = Coloms[2].y;
	result[2][2] = Coloms[2].z;

	return result;
}




 std::ostream& operator<<(std::ostream& stream, const Matrix3X3& maxtrix)
 {
	 stream << maxtrix.Coloms[0].x << " " << maxtrix.Coloms[1].x << " " << maxtrix.Coloms[2].x << " ";
	 stream << '\n';
	 stream << maxtrix.Coloms[0].y << " " << maxtrix.Coloms[1].y << " " << maxtrix.Coloms[2].y << " ";
	 stream << '\n';
	 stream << maxtrix.Coloms[0].z << " " << maxtrix.Coloms[1].z << " " << maxtrix.Coloms[2].z << " ";
	

	 return stream;
 }





