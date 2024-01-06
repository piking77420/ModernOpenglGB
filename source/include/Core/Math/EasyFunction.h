#pragma once
#include "ToolBoxMathHeaders.h"

namespace Math
{
	template<class T>
	[[nodiscard]]
	constexpr __forceinline T Lerp(const T& t0, const T& t2, float t)
	{
		return t0 * (1.f - t) + t2 * t;
	}	

	template<typename T>
	[[nodiscard]]
	constexpr int Sign(T t1)
	{
		if (t1 < static_cast<T>(0))
			return -1;

		if (t1 > static_cast<T>(0))
			return 1;

		return static_cast<T>(0);
	}
}