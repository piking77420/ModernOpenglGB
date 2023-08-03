#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>
#define cot(x) (cos(x)/sin(x))

#define TOLERANCE 0.000001f
#define GRAVITY 9.81f

namespace Math
{
	constexpr float Epsilon()
	{
		return std::numeric_limits<float>::epsilon();
	}


	inline bool epsilonEqual
	(
		double const& x,
		double const& y,
		double const& epsilon
	)
	{
		return abs(x - y) < epsilon;
	}

	inline bool epsilonNotEqual(float const& x, float const& y, float const& epsilon)
	{
		return abs(x - y) >= epsilon;
	}

	
	
	constexpr static inline float RadiansToDegrees(float radiant)
	{
		return radiant * 180.f / M_PI;
	}

	constexpr static inline float DegreesToRadians(float degrees)
	{
		return degrees * M_PI / 180.0;
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



}

