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
	Vector operator=(Vector Row0);


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

