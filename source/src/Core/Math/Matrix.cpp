#include "Matrix.h"
#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"
#include "Matrix4X4.h"




std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
	  


	size_t maxSize = 0; // Maximum size among all rows

	// Find the maximum size among all rows
	for (size_t k = 0; k < matrix.Size(); k++)
	{
		if (matrix[k].Size() > maxSize)
		{
			maxSize = matrix[k].Size();
		}
	}

	// Print the matrix elements
	for (size_t i = 0; i < maxSize; i++)
	{
		for (size_t k = 0; k < matrix.Size(); k++)
		{
			if (i > matrix[k].Size())
			{
				stream << "$" << " ";
			}
			else
			{
				stream << matrix[k].data[i] << " ";
			}
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

Matrix::operator Matrix4X4()
{
	Matrix4X4 result = Matrix4X4::Identity();

	int sizeVector = this->mData.size();
	int DimensionVector = 0;
	for (size_t i = 0; i < this->mData.size(); i++)
	{
		if (DimensionVector < mData[i].Size())
			DimensionVector = mData[i].Size();
	}
	if (sizeVector > 4)
	{
		sizeVector = 4;
	}
	if (DimensionVector > 4)
	{
		DimensionVector = 4;
	}
	
	float* data = result.SetPtr();

	for (size_t x = 0; x < sizeVector; x++)
	{
		for (size_t y = 0; y < DimensionVector; y++)
		{
			data[(x * sizeVector) + y] = mData[x][y];
		}
	}

	return result;
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

Matrix Matrix::Transposate()
{

	int numRows = this->Size();
	int numCols = mData[0].Size();
	Matrix transposedMatrix(numCols, numRows);


	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			transposedMatrix[j][i] = this->mData[i][j];
		}
	}

	return transposedMatrix;
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
	float max = std::abs(matrix[r][j]);

	for (int i = currentLign; i < matrix.Size(); i++)
	{
		if (std::abs(matrix[i][j]) > max)
		{
			max = std::abs(matrix[i][j]);
			indexmax = i;
		}
	}

	return indexmax;
}

void SwapVector(Vector* v1,Vector* v2)
{
	Vector tmpr = *v1;
	*v1 = *v2;
	*v2 = tmpr;
}



Matrix Matrix::PivotDeGauss()
{
	Matrix matrix = *this;

	int numRows = matrix.Size();
	int numCols = matrix[0].Size();

	int r = 0; 

	for (int j = 0; j < numCols; j++) {
		int k = r; 

		for (int i = r + 1; i < numRows; i++) {
			if (std::abs(matrix[i][j]) > std::abs(matrix[k][j])) {
				k = i;
			}
		}

		if (matrix[k][j] == 0) {
			continue;
		}

		SwapVector(&matrix[k], &matrix[r]);

		float divisor = matrix[r][j];
		for (int c = j; c < numCols; c++) {
			matrix[r][c] /= divisor;
		}

		for (int i = 0; i < numRows; i++) {
			if (i != r) {
				float factor = matrix[i][j];
				for (int c = j; c < numCols; c++) {
					matrix[i][c] -= factor * matrix[r][c];
				}
			}
		}

		r++;
	}

	return matrix;


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
	int SizeX = matrix[0].Size() - 1;
	int SizeY = matrix.Size() - 1 ;


	Matrix result = Matrix(SizeY, SizeX);

	size_t result_i = 0;  // Indice pour parcourir la matrice `result`

	for (size_t i = 0; i <= SizeX; i++)
	{
		if (i == index)
		{
			continue;  
		}

		size_t result_n = 0;  

		for (size_t n = 0; n <= SizeY; n++)
		{
			if (n == index)
			{
				continue;  
			}

			result[result_i][result_n] = matrix[i][n];
			result_n++; 
		}

		result_i++;  
	}
	


	return result;

}


float Matrix::CalculateDertimant(const Matrix& matrix)
{
	float result = 0;

	if (matrix.Size() != 2 && matrix[0].data.size() != 2)
	{
		for (size_t i = 0; i < matrix[0].Size(); i++)
		{

			if (i % 2 == 0)
			{
				result += matrix[0][i] * CalculateDertimant(SubDivideMatrix(matrix, i));

			}
			else
			{
				result -= matrix[0][i] * CalculateDertimant(SubDivideMatrix(matrix, i));

			}
		}
	}
	else
	{

		result += Determianant2x2(matrix);

	}


	return result;
}

Matrix Matrix::ReturnAugmentedMatrix(const Matrix& base, const Matrix& added)
{
	Matrix result = base;

	int baseM = base.mData.size();
	int baseN = base[0].data.size();
	int addedM = added.mData.size();
	int addedN = added[0].data.size();




	for (size_t i = 0; i < added.mData.size(); i++)
	{
		result.mData.push_back(added.mData[i]);

	}


	return result;

}


Matrix Matrix::ReturnInv()
{
	Matrix copy = *this;

	float determiant = Matrix::CalculateDertimant(copy);
	
	if (determiant == 0)
		return copy;

	copy = ReturnAugmentedMatrix(copy, copy.Identity(copy.mData.size()));

	copy = copy.PivotDeGauss();

	int lignSize = copy[0].data.size();
	int ligneSize2 = lignSize / 2;

	Matrix result(copy[0].data.size(), copy[0].data.size());


	for (size_t x = 0; x < result.Size(); x++)
	{
		for (size_t y = 0; y < result[0].Size(); y++)
		{
			result[x][y] =  copy[result.Size() + x][y];
		}
	}


	return result;



}

