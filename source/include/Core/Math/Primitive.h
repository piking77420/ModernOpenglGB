#pragma once
#include "Vector3.h"
#include "Vector4.h"


class Primitive
{
public:



	virtual Vector3 ConverToLocalCoordinate();
	Primitive();
	~Primitive();
};

