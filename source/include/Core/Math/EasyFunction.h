
#pragma once
#include "ToolBoxMathHeaders.h"

namespace Math
{
	template<class T>
	static inline T Lerp(const T& startValue, const T& endValue, float prt)
	{
		return (startValue + (endValue - startValue) * prt);
	}



	[[nodiscard]]
	static inline Vector3 Slerp(const Vector3& p0, const Vector3& p1, float t) noexcept
	{
		float angle = Vector3::Angle(p0, p1);

		float value0 = (std::sin((1 - t) * angle) / sin(angle));
		float value1 = (std::sin(t * angle) / std::sin(angle));

		return  p0 * value0 + p1 * value1;
	}
}