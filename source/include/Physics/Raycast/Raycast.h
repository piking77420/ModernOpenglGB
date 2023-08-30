#pragma once
#include "ToolBoxMathHeaders.h"
#include <limits>


struct Raycast
{
	Vector3 origin;
	Vector3 direction;
	float distance = std::numeric_limits<float>::infinity();


	Raycast(const Vector3& _origin, const Vector3& _direction) : origin(_origin) ,direction(_direction) 
	{

	}

	Raycast(const Vector3& _origin, const Vector3& _direction, const float _distance) : Raycast(_origin, _direction)
	{ 
		this->distance = _distance;

	}
	~Raycast() {};
};

