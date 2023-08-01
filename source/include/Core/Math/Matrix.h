#pragma once
#include<vector>
#include "ToolBoxMathHeaders.h"


class Vector3;
class Vector2;
class Vector;
class Matrix4X4;
class Matrix3X3;


class Matrix
{
public:

	
	int const Size() const ;
	std::vector<Vector> mData;


	


	Matrix Transposate();
	static Matrix Identity(const int size) ;
	static Matrix Identity(const int sizeX , const int sizeY);
	static Matrix ReturnAugmentedMatrix(const Matrix& base, const Matrix& added);

	Matrix Invert();
	void AddInMatrixVector(const Vector& Row0);
	static Matrix SubDivideMatrix(const Matrix& matrix, int index);
	static float CalculateDertimant(const Matrix& matrix);	
	Matrix PivotDeGauss();




#pragma region Operator

	Vector& operator[](int i);
	Vector operator[](int i) const;

	Matrix operator+(const Matrix& max2);
	Matrix operator-(const Matrix& max2);
	Matrix operator*(const float value);
	Vector operator*(const Vector& matrix);
	Matrix operator*(const Matrix& Vector);


	explicit operator Matrix4X4();
	explicit operator Matrix3X3();


#pragma endregion

	Matrix(const int size);
	Matrix(const int lign, const int coloms);
	Matrix();
	~Matrix();

private:

};



std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);



