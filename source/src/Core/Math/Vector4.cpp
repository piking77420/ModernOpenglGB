#include "Vector4.h"
#include <math.h>
#include <iostream>
#include "Vector3.h"




const Vector4 Vector4::Zero = Vector4(0,0,0,0);
const Vector4 Vector4::One = Vector4(1, 1, 1, 1);




float Vector4::operator[](const int& i) const
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else if (i == 2)
	{
		return z;
	}
	else if (i == 3)
	{
		return z;
	}
	return -99999999999;

}

float& Vector4::operator[](const int& i)
{
	// // O: insert return statement here

	if (i == 0)
	{
		return x;
	}
	else if( i == 1 )
	{
		return y;
	}
	else if (i == 2)
	{
		return z;
	}
	else if (i == 3)
	{
		return z;
	}


	
}


Vector4 Vector4::operator+(float value)
{
	return Vector4(x + value, y + value, z + value, w + value);

}



Vector4 Vector4::operator-(float value)
{
	return Vector4(x - value, y - value, z - value, w - value);

}

Vector4 Vector4::operator/(float value)
{
	return Vector4(x / value, y / value, z / value, w / value);

}


Vector4 Vector4::operator*(float value)
{

	return Vector4(x * value, y * value, z * value, w * value);
}
Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{
}

Vector4::Vector4() : x(0), y(0), z(0), w(0)
{
	
}

Vector4::~Vector4()
{
}




const float* Vector4::GetPtr() const 
{
	return &x;
}

Vector4::Vector4(const Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = 1;

}

float Vector4::Norm() const
{
	float result = powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2);

	return sqrtf(result) ;
}

Vector4 Vector4::Normalize() const
{
	float norm = Norm();

	Vector4 result = *this;

	result.x /= norm;
	result.y /= norm;
	result.z /= norm;
	result.w /= norm;



	return Vector4();
}

float* Vector4::SetPtr()
{
	return &x;
}


float Vector4::DotProduct(const Vector4& Row0) const
{
	float result = 0;

	result += (x * Row0.x);
	result += (y * Row0.y);
	result += (z * Row0.z);
	result += (w * Row0.w);

	

	//std::cout << result << std::endl;

	return result;
}



float Vector4::DotProduct(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.DotProduct(vec2);
}


float Vector4::Angle(const Vector4& vec1, const Vector4& vec2)
{
	float dot = DotProduct(vec1, vec2);
	float normVec1 = vec1.Norm();
	float normVec2 = vec2.Norm();
	float angle = std::acos(dot / (normVec1 * normVec2));
	return angle;
}
std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << '\n';

	return stream;
}








