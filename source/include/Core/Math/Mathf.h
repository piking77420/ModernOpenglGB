#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include "Matrix.h"
#include"Matrix2X2.h"
#include"Matrix3X3.h"
#include"Matrix4X4.h"
#include"Vector.h"
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"


#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define cot(x) (cos(x)/sin(x))

#define TOLERANCE 0.000001f
#define GRAVITY 4.81f




class Mathf
{
public:


	
	bool static IsEqual(float value , float value2);

	static inline float Abs(float value)
	{
		if (value < 0)
			return -value;

		return value;
	}


	static inline Vector2 Lerp(Vector2 startValue, Vector2 endValue, float prt)
	{
		return (startValue + (endValue - startValue) * prt);
	}
	static inline Vector4 Lerp(Vector4 startValue, Vector4 endValue, float prt)
	{
		return (startValue + (endValue - startValue) * prt);
	}
	

	static float minimum(float x, float y)
	{
		if (x < y)
		{
			return x;

		}
		else
		{
			return y;

		}
	}static float maximum(float x, float y)
	{	
		if (x > y)
			return x;
		else
		{
			return y;

		}
	}

	Mathf();
	~Mathf();

private:

};


static inline float Lerp(float startValue, float endValue, float prt)
{
	return (startValue + (endValue - startValue) * prt);
}