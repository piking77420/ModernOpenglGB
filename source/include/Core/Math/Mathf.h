#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <iostream>
#include <algorithm>
#include "Matrix.h"
#include"Matrix2X2.h"
#include"Matrix3X3.h"
#include"Matrix4X4.h"
#include"Vector.h"
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include "Quaternion.h"

#define cot(x) (cos(x)/sin(x))

#define TOLERANCE 0.000001f
#define GRAVITY 4.81f



namespace Math
{

	
	
	static inline float RadiansToDegrees(float radiant)
	{
		return radiant * 180.f / M_PI;
	}

	static inline float DegreesToRadians(float degrees)
	{
		return degrees * M_PI / 180.0;
	}

	template<class T>
	static inline T Lerp(const T& startValue, const T& endValue, float prt)
	{
		return (startValue + (endValue - startValue) * prt);
	}
	
	
	// Fast std::Sqrtf base on Quake3 32bits  
	constexpr static inline double FSqrtf(float value)
	{

		long long i = 0;
		double x2 = 0 , y = 0 ;
		const double threehalfs = 1.5;

		x2 = value * 0.5;
		y = value;
		i = *(long long*)&y;
		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(double*)&i;
		y = y * (threehalfs - x2 * y * y);
		y = y * (threehalfs - x2 * y * y); // 2ns iteration not nessecry
		return 1/(float)y;
	}

	inline Vector3 ToCylinderCoordiante(const Vector3& pos)
	{
		return Vector3(Math::FSqrtf(pos.x * pos.x + pos.y * pos.y), std::atan2f(pos.y, pos.x), pos.z);
	}
	inline Vector3 CylinderCoordianteToCartesian(const Vector3& pos, float angle)
	{
		return Vector3(pos.x * std::cosf(angle), pos.y * std::sinf(angle), pos.z);
	}

	inline Vector3 ToSphericalCoordiante(float rayon,float delta,float theta)
	{
		return Vector3(rayon * std::sinf(delta) * std::cosf(theta), rayon * std::sinf(delta) * std::sinf(theta),rayon * std::cosf(delta));
	}
	// Retrun x = rayon , y = delta ,z = theta
	inline Vector3 SphericalCoordianteToCartesian(const Vector3& pos,float angle)
	{
		float rayon = pos.Norm();
		return Vector3(rayon,std::acosf(pos.z/ rayon),std::atan2f(pos.y,pos.x));
	}

}

