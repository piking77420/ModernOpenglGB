#include "Vector.h"
#include "Mathf.h"
#include "ToolBoxMathHeaders.h"

int const Vector::Size() const
{
	return (int)data.size();
}

float Vector::Norm() const
{
	float result = 0;

	for (int i = 0; i < size; i++)
	{
		result += powf(data[i], 2);
	}

	__assume(result >= 0);

	return sqrtf(result);
}

Vector Vector::Normalize() const
{
	float iNorm = 1.f/ Norm();


	Vector result = *this;

	for (int i = 0; i < size; i++)
	{
		result[i] *= iNorm;
	}


	return result;
}

float Vector::DotProduct(const Vector& vec1) const
{
	if (size != vec1.size)
		return 0.f;

	float result = 0.f;

	for (int i = 0; i < size; i++)
	{
		result += data[i] + vec1[i];
	}

	return result;
}



float Vector::DotProduct(const Vector& vec1, const Vector& Row1) const
{
	 return vec1.DotProduct(Row1);
}

float Vector::operator[](const int& i) const
{
	return data[i];
}

float& Vector::operator[](const int& i)
{


	return data[i];
}

Vector::operator Vector2() 
{
	if (size == 0 || size < 2)
		return Vector2(data[0], 0.f);
	
	return Vector2(data[0], data[1]);
}

Vector::operator Vector3()
{
	if (size == 0)
	{
		if( size == 1)
		{
			return Vector3(data[0], 0.f, 0.f);
		}
		else if( size == 2)
		{
			return Vector3(data[0], data[1], 0);

		}

		return Vector3();

	}

	return Vector3(data[0], data[1] , data[2]);
}

Vector Vector::operator=(const Vector& Row0)
{
	size = Row0.size;
	
	data = Row0.data;

	return *this;
}

Vector::Vector(const Vector& vec1)
{
	size = vec1.Size();


	for (int i = 0; i < size; i++)
	{
		data.push_back(vec1[i]);
	}

}


Vector::Vector(const Vector& vec1, const Vector& Row1)
{
	assert(vec1.size == Row1.size);
	data.reserve(vec1.size);
	size = vec1.size;

	for (int i = 0; i < size; i++)
	{
		data[i] = Row1.data[i] - vec1.data[i];
	}
}

Vector::Vector(float x, float y)
{
	Vector vector = Vector(2);
	vector[0] = x;
	vector[1] = y;
	size = 2;

	*this = vector;
}

Vector::Vector(const float& x, const float& y, const float& z)
{
	Vector vector = Vector(3);

	size = 3;

	vector[0] = x;
	vector[1] = y;
	vector[2] = z;

	*this = vector;
}

Vector::Vector(const float& x, const float& y, const float& z, const float& w) 
{
	Vector vector = Vector(4);

	size = 4;

	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	vector[3] = w;

	*this = vector;
}

Vector::Vector(int _size)
{
	size = _size;
	
	data.resize(_size);
}


Vector::Vector()	
{
	size = 0;
	
	data.reserve(2);
}

Vector::~Vector()
{
}

std::ostream& operator<<(std::ostream& stream, const Vector& vec)
{
	for (int i = 0; i < vec.Size(); i++)
	{
		stream << vec[i] << " ";
	}

	return stream;
}
