#pragma once
#include<iostream>
#include <vector>
#include "Matrix3X3.h"
#define _USE_MATH_DEFINES
#include <cassert>
#include<math.h>



class Vector3;
class Vector2;
class Vector;
class Matrix4X4;


class Matrix
{
public:

	
	int const Size() const ;
	std::vector<Vector> mData;


	


	Matrix Transposate();
	static Matrix Identity(const int size) ;
	static Matrix Identity(const int sizeX , const int sizeY);

	static Matrix TranslateMatrix2x2(float x , float y);
	static Matrix TranslateMatrix3X3(Vector translation);
	static Matrix TranslateMatrix4X4(Vector translation);


	// Degres
	static Matrix RotationMatrix2x2(float angleD);


	static Matrix RotationXMatrix3X3(float angle);
	static Matrix RotationYMatrix3X3(float angle);
	static Matrix RotationZMatrix3X3(float angle);
	static Matrix RotationMatrix(Vector angles);

	static Matrix ScalingMatrix2X2(const Vector& values);
	static Matrix ScalingMatrix3X3(const Vector& values);



	static Matrix RotationMatrixTRS(Vector Translation, Vector rotation, Vector scaling);

	static Matrix ReturnAugmentedMatrix(const Matrix& base, const Matrix& added);

	Matrix ReturnInv();
	void AddInMatrixVector(const Vector& Row0);
	Matrix MatrixToHomogeneus() const ;

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


#pragma endregion

	Matrix(const int size);
	Matrix(const int lign, const int coloms);
	Matrix();
	~Matrix();

private:

};



std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);



