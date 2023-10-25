#pragma once
#include <iostream>
#include <vector>


class Vector2;
class Vector3;

class Vector
{
public:

	int size;
	std::vector<float> data;

	
	int const Size() const ;

#pragma region function



	float Norm() const;

	Vector Normalize() const;

	float DotProduct(const Vector& vec1) const;

	
	float DotProduct(const Vector& vec1 , const Vector& Row1) const;

#pragma endregion


	float operator[](const int& i) const;
	float& operator[](const int& i);
	explicit operator Vector2();
	explicit operator Vector3();
	Vector operator=(const Vector& Row0);


	Vector(const Vector& vec1);
	Vector(const Vector& vec1, const Vector& Row1);
	Vector(float x , float y );
	Vector(const float& x, const float& y , const float& z);
	Vector(const float& x, const float& y, const float& z , const float& w);

	Vector(int _size);
	Vector();
	~Vector();

	
	// TO DO operator Matrix



private:

};


std::ostream& operator<<(std::ostream& stream, const Vector& vec);


inline Vector operator+(const Vector& vec1, const Vector& vec2)
{
	int size1 = vec1.Size();
	int size2 = vec2.Size();

	int lessSize;
	int GreaterSize;
	Vector result;

	if (size1 < size2)
	{
		lessSize = size1;
		GreaterSize = size2;
		result = vec2;


		for (int i = 0; i < lessSize; i++)
		{
			result[i] += vec1[i];
		}
	}
	else
	{
		lessSize = size2;
		GreaterSize = size1;
		result = vec1;


		for (int i = 0; i < lessSize; i++)
		{
			result[i] += vec2[i];
		}
	}

	return result;

}


inline Vector operator-(const Vector& vec1, const Vector& vec2)
{
	int size1 = vec1.Size();
	int size2 = vec2.Size();

	int lessSize;
	int GreaterSize;
	Vector result;

	if (size1 < size2)
	{
		lessSize = size1;
		GreaterSize = size2;
		result = vec2;


		for (int i = 0; i < lessSize; i++)
		{
			result[i] -= vec1[i];
		}
	}
	else
	{
		lessSize = size2;
		GreaterSize = size1;
		result = vec1;


		for (int i = 0; i < lessSize; i++)
		{
			result[i] -= vec2[i];
		}
	}

	return result;

}