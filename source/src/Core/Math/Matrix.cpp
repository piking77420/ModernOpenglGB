#include "Matrix.h"
#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"



std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
	/// 
	///  X X X 
	///  Y Y Y
	///  Z Z Z
	///	  

	for (size_t i = 0; i < matrix.Size(); i++)
	{
		
		for (size_t k = 0; k < matrix[i].data.size(); k++)
		{
			
			
				stream << matrix[i].data[k] << " ";

		}

		stream << '\n';
	}
	

	return stream;
}


Vector& Matrix::operator[](int i)
{
	

	return mData[i];
}

Vector Matrix::operator[](int i) const
{
	return mData[i];
}






int ReturnGreaterMatrix(const Matrix& max1, const Matrix& max2)
{

	if (max1.Size() >= max2.Size())
	{
		return max1.Size();
	}
	else if (max1.Size() < max2.Size())
	{
		return max2.Size();
	}
	

	std::cout << "Shoundl be here " << '\n';
	return 0;
}

Matrix Matrix::operator+(const Matrix& maxtrix)
{
	int sizNewMatrix = ReturnGreaterMatrix(*this, maxtrix);
	Matrix newMatrix = Matrix(sizNewMatrix);
	for (size_t i = 0; i < newMatrix.Size(); i++)
	{
		for (size_t k = 0; k < newMatrix.mData[i].Size(); k++)
		{
			newMatrix[i][k] = mData[i][k] + maxtrix[i][k];
		}
	}

	return newMatrix;
}

Matrix Matrix::operator*(const float value)
{
	Matrix newMatrix = Matrix(this->Size() ,this->mData[0].Size());

	for (size_t i = 0; i < newMatrix.Size(); i++)
	{
		for (size_t k = 0; k < newMatrix[i].Size(); k++)
		{
			newMatrix = mData[i][k] * value;
		}
	}

	return Matrix();
}

Vector Matrix::operator*(const Vector& vector)
{
	


	Vector result(mData[0].data.size());

	for (size_t i = 0; i < mData.size(); i++)
	{
		for (size_t j = 0; j < mData[0].data.size(); j++)
		{
			result[i] += mData[i][j] * vector[i];
		}
	}

	return result;


	
	return Vector();
}

Matrix Matrix::operator*(const Matrix& matrix)
{

	int NbrOfVector = this->Size();
	int SizeOfVector = matrix.mData[0].data.size();
	


	Matrix newMatrix = Matrix(NbrOfVector, SizeOfVector);

	for (size_t i = 0; i < newMatrix.Size() ; i++)
	{
		for (size_t k = 0; k < NbrOfVector ; k++)
		{
			for (size_t l = 0; l < NbrOfVector ; l++)
			{
				newMatrix.mData[k].data[i] += mData[l].data[i] * matrix.mData[k].data[l];


			}

		}
	}


	return newMatrix;
}


Matrix Matrix::operator-(const Matrix& maxtrix)
{
	int sizNewMatrix = ReturnGreaterMatrix(*this, maxtrix);
	Matrix newMatrix = Matrix(sizNewMatrix);
	for (size_t i = 0; i < newMatrix.Size(); i++)
	{
		for (size_t k = 0; k < newMatrix.mData[i].Size(); k++)
		{
			newMatrix[i][k] = mData[i][k] - maxtrix[i][k];
		}
	}

	return newMatrix;
}



Matrix::Matrix(const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		mData.push_back(Vector(size));
	}

}

Matrix::Matrix(const int lign , const int coloms)
{
	for (size_t i = 0; i < lign; i++)
	{
		Vector newVec = Vector(coloms);
		mData.push_back(newVec);
	}

}


Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

int const Matrix::Size() const
{
	return mData.size();
}

Matrix Matrix::Identity(const int size)
{
	Matrix matrix(size);
	
	for (size_t i = 0; i < matrix.mData.size() ; i++)
	{	
			matrix[i].data[i] = 1;
	}


	return matrix;
}

Matrix Matrix::Identity(const int sizeX, const int sizeY)
{
	Matrix result = Matrix(sizeX, sizeY);


	for (size_t i = 0; i < sizeX; i++)
	{
		result[i].data[i] = 1;
	}



	return result;
}

Matrix Matrix::TranslateMatrix2x2(float x, float y)
{
	Matrix NewMatrix = Matrix(2);


	NewMatrix.mData[1][0] = x;
	NewMatrix.mData[1][1] = y;

	return NewMatrix;

}

Matrix Matrix::TranslateMatrix3X3(Vector translation)
{
	Matrix NewMatrix = Matrix(3);


	NewMatrix.mData[2][0] = translation[0];
	NewMatrix.mData[2][1] = translation[1];
	NewMatrix.mData[2][2] = translation[2];


	return NewMatrix;
}



Matrix Matrix::TranslateMatrix4X4(Vector translation)
{
	Matrix NewMatrix = Matrix(4);


	NewMatrix[0][0] = 1;
	NewMatrix[1][1] = 1;
	NewMatrix[2][2] = 1;



	NewMatrix[3][0] = translation[0];
	NewMatrix[3][1] = translation[1];
	NewMatrix[3][2] = translation[2];
	NewMatrix[3][3] = 1;



	return NewMatrix;
}


Matrix Matrix::RotationMatrix2x2(float angle)
{
	Matrix NewMatrix = Matrix(2);


	NewMatrix.mData[0][0] = cosf(degreesToRadians(angle));
	NewMatrix.mData[1][0] = -sinf(degreesToRadians(angle));

	NewMatrix.mData[0][1] = sinf(degreesToRadians(angle));
	NewMatrix.mData[1][1] = cosf(degreesToRadians(angle));


	return NewMatrix;
}

Matrix Matrix::RotationXMatrix3X3(float angle)
{
	Matrix NewMatrix = Matrix(3);



	NewMatrix[0][0] = 1;
	NewMatrix[0][1] = 0;
	NewMatrix[0][2] = 0;

	NewMatrix[1][0] = 0;
	NewMatrix[1][1] = cos(degreesToRadians(angle));
	NewMatrix[1][2] = sin(degreesToRadians(angle));

	NewMatrix[2][0] = 0;
	NewMatrix[2][1] = -sin(degreesToRadians(angle));
	NewMatrix[2][2] = cos(degreesToRadians(angle));


	

	return NewMatrix;
}

Matrix Matrix::RotationYMatrix3X3(float angle)
{
	Matrix NewMatrix = Matrix(3);



	NewMatrix[0][0] = cos(degreesToRadians(angle));
	NewMatrix[0][1] = 0;
	NewMatrix[0][2] = -sin(degreesToRadians(angle));

	NewMatrix[1][0] = 0;
	NewMatrix[1][1] = 1;
	NewMatrix[1][2] = 0;

	NewMatrix[2][0] = sin(degreesToRadians(angle));
	NewMatrix[2][1] = 0;
	NewMatrix[2][2] = cos(degreesToRadians(angle));


	return NewMatrix;
}

Matrix Matrix::RotationZMatrix3X3(float angle)
{
	Matrix NewMatrix = Matrix(3);



	NewMatrix[0][0] = cos(degreesToRadians(angle));
	NewMatrix[0][1] = sin(degreesToRadians(angle));
	NewMatrix[0][2] = 0;

	NewMatrix[1][0] = -sin(degreesToRadians(angle));
	NewMatrix[1][1] = cos(degreesToRadians(angle));
	NewMatrix[1][2] = 0;

	NewMatrix[2][0] = 0;
	NewMatrix[2][1] = 0;
	NewMatrix[2][2] = 1;


	return NewMatrix;
}

Matrix Matrix::RotationMatrix(Vector angles)
{
	Matrix RotationMatrix = Matrix(3);



	RotationMatrix = RotationYMatrix3X3(angles[1]) *  RotationZMatrix3X3(angles[2]);

	RotationMatrix = RotationXMatrix3X3(angles[0]) * RotationMatrix;

	std::cout << RotationMatrix << std::endl;





	return RotationMatrix;
}

Matrix Matrix::ScalingMatrix2X2(const Vector& values)
{
	Matrix NewMatrix = Matrix(2);


	NewMatrix.mData[0][0] = values[0];
	NewMatrix.mData[1][0] = 0;

	NewMatrix.mData[0][1] = 0;
	NewMatrix.mData[1][1] = values[1];

	return NewMatrix;

}

Matrix Matrix::ScalingMatrix3X3(const Vector& values)
{
	
	Matrix NewMatrix = Matrix(3);

	

	NewMatrix[0][0] = values[0];
	NewMatrix[0][1] = 0;
	NewMatrix[0][2] = 0;

	NewMatrix[1][0] = 0;
	NewMatrix[1][1] = values[1];
	NewMatrix[1][2] = 0;

	NewMatrix[2][0] = 0;
	NewMatrix[2][1] = 0;
	NewMatrix[2][2] = values[2];


	return NewMatrix;
}


// Vector3
Matrix Matrix::RotationMatrixTRS(Vector Translation, Vector rotation, Vector scaling)
{

	Matrix scalingMaxtrix = ScalingMatrix3X3(scaling).MatrixToHomogeneus();
	Matrix rotationMaxtrix = RotationMatrix(rotation).MatrixToHomogeneus();
	Matrix translationMaxtrix = TranslateMatrix4X4(Translation);



	Matrix TRS = translationMaxtrix * rotationMaxtrix * scalingMaxtrix;
	return TRS;
}





void Matrix::AddInMatrixVector(const Vector& Row0)
{
	this->mData.push_back(Row0);
}

Matrix Matrix::MatrixToHomogeneus() const
{


	int nbrOfVector = Size();
	int SizeOfVector = mData[0].Size();
	if (nbrOfVector != SizeOfVector || nbrOfVector >= 4 && SizeOfVector >= 4)
	{
		return Matrix();
	}

	Matrix Newmatrix = Matrix(4);
	

	for (size_t i = 0; i < nbrOfVector; i++)
	{
		for (size_t k = 0; k < SizeOfVector; k++)
		{
			Newmatrix[i][k] = this->mData[i][k];
		}
		
	}
	Newmatrix[3][0] = 0;
	Newmatrix[3][1] = 0;
	Newmatrix[3][2] = 0;
	Newmatrix[3][3] = 1;


	Newmatrix[0][3] = 0;
	Newmatrix[1][3] = 0;
	Newmatrix[2][3] = 0;



	return Newmatrix;
}


float ReturnAbsol(float value)
{
	if (value < 0)
	{
		value = -value;
	}

	return value;
}




int returnMaxInColomm(Matrix& matrix, const int& r, const int& j)
{
	int indexmax = r;
	int currentLign = r;
	float max = ReturnAbsol(matrix[r][j]);

	// cout << " here "<< r << "  matrix.Vectors.size() - r" << endl;
	for (size_t i = currentLign; i < matrix.Size() - r; i++)
	{

		if (ReturnAbsol(matrix[i][j]) > ReturnAbsol(max))
		{

			max = ReturnAbsol(matrix[i][j]);

			indexmax = i;
		}

	}

	return indexmax;	
}





Matrix Matrix::PivotDeGauss()
{

	Matrix result = *this;
	//cout << result << endl;

	int r = 0;
	int n = this->Size(); // nbr of ligne
	int i = this->mData[0].data.size(); /// taile d'une ligne 

	for (size_t j = 0; j < n; j++)
	{
		//cout << endl << endl << " Loop " << j << endl << result << endl;

		int k = returnMaxInColomm(result, r, j);

		//cout << "where is the Maximum " << k << endl;

		if (result[k][j] != 0)
		{



			float toDivide = result[k][j];

			for (size_t l = 0; l < i; l++)
			{
				//cout << result[k][l] << "/" << toDivide << endl;
				result[k][l] = result[k][l] / toDivide;
				//cout << "result = " << result[k][l] << endl;

			}
			//cout << result << endl;

			//cout << " k = " << k << " " << " r  = " << r << endl;
			if (k != r)
			{
				std::swap(result[k], result[r]);
			}
			//cout << result << endl;


			for (size_t m = 0; m < n; m++)
			{
				//cout << "m = " << m << " r = " << r << endl;
				if (m != r)
				{
					float alpha = result[m][j];
					for (size_t l = 0; l < i; l++)
					{
						//cout << result[m][l] << " -= " << alpha << " * " << result[r][l] << endl;
						result[m][l] -= alpha * result[r][l];
						//cout << "result = " << result[m][l] << endl;
					}
				}
			}


			// cout << result << endl;
			r++;




		}


	}


	return result;
}

/*
Matrix::operator Matrix3X3()
{
	

	Matrix3X3 result; 

	for (size_t i = 0; i < 3; i++)
	{
		result.Ligns[i].x = mData[i][0];
		result.Ligns[i].y = mData[i][1];
		result.Ligns[i].z = mData[i][2];
	}


	return result;

}

*/


float Determianant2x2(const  Matrix& matrix)
{
	float returnValue = 0;

	returnValue = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];


	return returnValue;
}



Matrix Matrix::SubDivideMatrix(const Matrix& matrix, int index)
{
	Matrix result = matrix;


	result.mData.erase(next(result.mData.begin(), index));

	for (size_t i = 0; i < result.Size(); i++)
	{
		result[i].data.erase(result[i].data.begin());
	}

	return result;

}


float Matrix::CalculateDertimant(const Matrix& matrix)
{
	float result = 0;

	if (matrix.Size() != 2 && matrix[0].data.size() != 2)
	{
		for (size_t i = 0; i < matrix[i].Size(); i++)
		{

			if (i % 2 == 0)
			{
				result += matrix[i][0] * CalculateDertimant(SubDivideMatrix(matrix, i));

			}
			else
			{
				result -= matrix[i][0] * CalculateDertimant(SubDivideMatrix(matrix, i));

			}
		}
	}
	else
	{

		result += Determianant2x2(matrix);

	}


	return result;
}

Matrix ReturnAugmentedMatrix(const Matrix& base, const Matrix& added)
{
	Matrix result = base;

	int baseM = base.mData.size();
	int baseN = base[0].data.size();
	int addedM = added.mData.size();
	int addedN = added[0].data.size();




	for (size_t i = 0; i < added.mData.size(); i++)
	{
		for (size_t k = 0; k < added.mData[i].data.size(); k++)
		{
			result.mData[i].data.push_back(added.mData[i].data[k]);

		}

	}


	return result;

}


Matrix Matrix::ReturnInv()
{
	Matrix copy = *this;




	copy = ReturnAugmentedMatrix(copy, copy.Identity(copy.mData.size()));
	std::cout << copy << std::endl;

	copy = copy.PivotDeGauss();

	int lignSize = copy[0].data.size();
	int ligneSize2 = lignSize / 2;

	Matrix result(copy.mData.size(), ligneSize2);

	for (size_t i = 0; i < copy.mData.size(); i++)
	{
		for (size_t k = ligneSize2; k < lignSize; k++)
		{
			result[i][k - ligneSize2] = copy[i][k];
		}
	}


	return result;



}

