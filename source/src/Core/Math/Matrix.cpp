#include "Matrix.h"

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
	if (matrix.mData.size() != 0)
	{
		for (unsigned int i = 0; i < matrix.mData.size(); i++)
		{
			stream << "VectorD at Matrix[" << i << "] = ";
			for (unsigned int k = 0; k < matrix.mData[i].data.size(); k++)
			{
				stream << matrix[i][k] << " ";
			}
			stream << std::endl;
		}
	}
	return stream;
}

Vector& Matrix::operator[](int i)
{
	assert(i >= 0 && i < Size());
	return mData[i];
}

Vector Matrix::operator[](int i) const
{
	assert(i >= 0 && i < Size());
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

	std::cout << "Shouldn't be here " << '\n';
	return 0;
}

Matrix Matrix::operator+(const Matrix& maxtrix)
{
	int sizNewMatrix = ReturnGreaterMatrix(*this, maxtrix);
	Matrix newMatrix = Matrix(sizNewMatrix);
	for (int i = 0; i < newMatrix.Size(); i++)
	{
		for (int k = 0; k < newMatrix.mData[i].Size(); k++)
		{
			newMatrix[i][k] = mData[i][k] + maxtrix[i][k];
		}
	}

	return newMatrix;
}

Matrix Matrix::operator*(const float value)
{
	Matrix newMatrix = Matrix(this->Size(), this->mData[0].Size());

	for (int i = 0; i < newMatrix.Size(); i++)
	{
		for (int k = 0; k < newMatrix[i].Size(); k++)
		{
			newMatrix[i][k] = mData[i][k] * value;
		}
	}

	return newMatrix;
}

Vector Matrix::operator*(const Vector& vector)
{
	Vector result((int)mData[0].data.size());

	for (unsigned int i = 0; i < mData.size(); i++)
	{
		for (int j = 0; j < (int)mData[0].data.size(); j++)
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
	int SizeOfVector = (int)matrix.mData[0].data.size();

	Matrix newMatrix = Matrix(NbrOfVector, SizeOfVector);

	for (int i = 0; i < newMatrix.Size(); i++)
	{
		for (int k = 0; k < NbrOfVector; k++)
		{
			for (int l = 0; l < NbrOfVector; l++)
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

	int sizeVector = (int)this->mData.size();
	int DimensionVector = 0;
	for (int i = 0; i < (int)this->mData.size(); i++)
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

	for (int x = 0; x < sizeVector; x++)
	{
		for (int y = 0; y < DimensionVector; y++)
		{
			data[(x * sizeVector) + y] = mData[x][y];
		}
	}

	return result.Transpose();
}

Matrix::operator Matrix3X3()
{
	Matrix3X3 result = Matrix3X3();

	int sizeVector = (int)this->mData.size();
	int DimensionVector = 0;
	for (int i = 0; i < (int)this->mData.size(); i++)
	{
		if (DimensionVector < mData[i].Size())
			DimensionVector = mData[i].Size();
	}
	if (sizeVector > 3)
	{
		sizeVector = 3;
	}
	if (DimensionVector > 3)
	{
		DimensionVector = 3;
	}

	float* data = result.SetPtr();

	for (int x = 0; x < sizeVector; x++)
	{
		for (int y = 0; y < DimensionVector; y++)
		{
			data[(x * sizeVector) + y] = mData[x][y];
		}
	}

	return result.Transpose();
}

Matrix Matrix::operator-(const Matrix& maxtrix)
{
	int sizNewMatrix = ReturnGreaterMatrix(*this, maxtrix);
	Matrix newMatrix = Matrix(sizNewMatrix);
	for (int i = 0; i < newMatrix.Size(); i++)
	{
		for (int k = 0; k < newMatrix.mData[i].Size(); k++)
		{
			newMatrix[i][k] = mData[i][k] - maxtrix[i][k];
		}
	}

	return newMatrix;
}



Matrix::Matrix(const int size)
{
	for (int i = 0; i < size; i++)
	{
		mData.push_back(Vector(size));
	}
}

Matrix::Matrix(const int lign, const int Columns)
{
	for (int i = 0; i < lign; i++)
	{
		Vector added = Vector(int(Columns));
		this->mData.push_back(added);
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
	return (int)mData.size();
}

Matrix Matrix::Transpose()
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

	for (unsigned int i = 0; i < matrix.mData.size(); i++)
	{
		matrix[i].data[i] = 1;
	}

	return matrix;
}

Matrix Matrix::Identity(const int sizeX, const int sizeY)
{
	Matrix result = Matrix(sizeX, sizeY);

	for (int i = 0; i < sizeX; i++)
	{
		result[i].data[i] = 1;
	}

	return result;
}

void Matrix::AddInMatrixVector(const Vector& Row0)
{
	this->mData.push_back(Row0);
}

float ReturnAbsol(float value)
{
	if (value < 0)
	{
		value = -value;
	}

	return value;
}

int returnMaxInColumn(Matrix& matrix, const int& r, const int& j)
{
	int indexmax = r;
	int currentLign = r;
	float max = ReturnAbsol(matrix[r][j]);

	for (unsigned int i = currentLign; i < matrix.mData.size() - r; i++)
	{
		if (ReturnAbsol(matrix[i][j]) > ReturnAbsol(max))
		{
			max = ReturnAbsol(matrix[i][j]);
			indexmax = i;
		}
	}

	return indexmax;
}

//Row Reduction by Gauss-Jordan, for matrix inversion
Matrix Matrix::GaussianElimination()
{
	Matrix result = *this;

	int r = 0;
	int n = (int)result.mData.size(); // number of line
	int i = (int)result.mData[0].data.size(); /// size of a line 

	for (int j = 0; j < n; j++)
	{
		int k = returnMaxInColumn(result, r, j);

		if (result[k][j] != 0)
		{
			float toDivide = result[k][j];

			for (int l = 0; l < i; l++)
			{
				result[k][l] = result[k][l] / toDivide;
			}

			if (k != r)
			{
				std::swap(result[k], result[r]);
			}

			for (int m = 0; m < n; m++)
			{
				if (m != r)
				{
					float alpha = result[m][j];
					for (int l = 0; l < i; l++)
					{
						result[m][l] -= alpha * result[r][l];
					}
				}
			}
			r++;
		}
	}

	return result;
}

float Determinant2x2(const  Matrix& matrix)
{
	float returnValue = 0;

	returnValue = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

	return returnValue;
}

Matrix Matrix::SubDivideMatrix(const Matrix& matrix, int index)
{
	int SizeX = matrix[0].Size() - 1;
	int SizeY = matrix.Size() - 1;

	Matrix result = Matrix(SizeY, SizeX);

	int result_i = 0;  // Index to read through the matrix `result`

	for (int i = 0; i <= SizeX; i++)
	{
		if (i == index)
		{
			continue;
		}

		int result_n = 0;

		for (int n = 0; n <= SizeY; n++)
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

float Matrix::CalculateDeterminant(const Matrix& matrix)
{
	float result = 0;

	if (matrix.Size() != 2 && matrix[0].data.size() != 2)
	{
		for (int i = 0; i < matrix[0].Size(); i++)
		{

			if (i % 2 == 0)
			{
				result += matrix[0][i] * CalculateDeterminant(SubDivideMatrix(matrix, i));

			}
			else
			{
				result -= matrix[0][i] * CalculateDeterminant(SubDivideMatrix(matrix, i));

			}
		}
	}
	else
	{
		result += Determinant2x2(matrix);
	}

	return result;
}

Matrix Matrix::ReturnAugmentedMatrix(const Matrix& base, const Matrix& added)
{
	Matrix result = base;

	int baseM = (int)base.mData.size();
	int baseN = (int)base[0].data.size();
	int addedM = (int)added.mData.size();
	int addedN = (int)added[0].data.size();

	assert((baseM == addedM, "Not same Size M"));

	for (unsigned int i = 0; i < added.mData.size(); i++)
	{
		for (unsigned int k = 0; k < added.mData[i].data.size(); k++)
		{
			result.mData[i].data.push_back(added.mData[i].data[k]);
		}
	}

	return result;
}

Matrix Matrix::Invert()
{
	Matrix copy = *this;

	float determiant = Matrix::CalculateDeterminant(copy);

	if (determiant == 0)
		return copy;

	copy = ReturnAugmentedMatrix(copy, copy.Identity((int)copy.mData.size()));

	copy = copy.GaussianElimination();

	int lignSize = (int)copy[0].data.size();
	int ligneSize2 = lignSize / 2;

	Matrix result((int)copy.mData.size(), ligneSize2);

	for (unsigned int i = 0; i < copy.mData.size(); i++)
	{
		for (int k = ligneSize2; k < lignSize; k++)
		{
			result[i][k - ligneSize2] = copy[i][k];
		}
	}

	return result;
}