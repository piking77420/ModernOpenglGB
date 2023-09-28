#pragma once
#include <iostream>
#include<cassert>
#include "Vector3.h"

class Vector2;
class Vector;

class Vector4
{
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	constexpr static uint16_t Size()
	{
		return 4;
	}

	[[nodiscard]]
	float Norm() const;
	[[nodiscard]]
	Vector4 Normalize() const;
	[[nodiscard]]
	constexpr inline static float DotProduct(const Vector4& vec1, const Vector4& vec2)
	{
			float result = 0;
			result += (vec1.x * vec2.x);
			result += (vec1.y * vec2.y);
			result += (vec1.z * vec2.z);
			result += (vec1.w * vec2.w);
			return result;
	}


	[[nodiscard]]
	static inline float Angle(const Vector4& vec1, const Vector4& vec2) 
	{
		float dot = DotProduct(vec1, vec2);
		float normVec1 = vec1.Norm();
		float normVec2 = vec2.Norm();
		float angle = std::acos(dot / (normVec1 * normVec2));
		return angle;
	}



#pragma region Operator

	constexpr inline float operator[](int i) const
	{
		return *static_cast<const float*>(&x + i);
	}
	constexpr inline float& operator[](int i)
	{
		return *static_cast<float*>(&x + i);
	}


	constexpr inline Vector4 operator+(float value)  const
	{
		return Vector4(x + value, y + value, z + value, w + value);
	}
	constexpr inline Vector4 operator-(float value) const
	{
		return Vector4(x - value, y - value, z - value, w - value);
	}
	constexpr inline Vector4 operator*(float value) const
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}

	constexpr inline Vector4 operator/(float value) const
	{
		return Vector4(x / value, y / value, z / value, w / value);
	}



#pragma region Operator

	inline Vector4 operator+(const Vector4& Row1) const
	{
		return Vector4(x + Row1.x, y + Row1.y, z + Row1.z, w + Row1.w);
	}
	inline Vector4 operator-(const Vector4& Row1) const
	{
		return Vector4(x - Row1.x, y - Row1.y, z - Row1.z, w - Row1.w);
	}
	
	inline Vector4 operator*(const Vector4& Row1) const
	{
		return Vector4(x * Row1.x, y * Row1.y, z * Row1.z, w / Row1.w);
	}
	inline Vector4 operator/(const Vector4& Row1) const
	{
		return Vector4(x / Row1.x, y / Row1.y, z / Row1.z, w / Row1.w);
	}


	inline void operator+=(float value)
	{
		x += value;
		y += value;
		z += value;
		w += value;

	}
	inline void operator-=(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
	}

	inline void operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
	}
	inline void operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
	}
	inline Vector4 operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}



	explicit operator Vector() const;
	explicit operator Vector2() const;
	explicit operator Vector3() const 
	{
		return Vector3(x, y, z);
	}


#pragma endregion

	[[nodiscard]]
	constexpr static inline float DistanceSquare(const Vector4& a, const Vector4& b)
	{
		return ((a.x - b.x * a.x - b.x) + (a.y - b.y * a.y - b.y) + (a.z - b.z * a.z - b.z) + (a.w - b.w * a.w - b.w));
	}
	[[nodiscard]]
	static inline float Distance(const Vector4& a, const Vector4& b)
	{
		return std::sqrt((a.x - b.x * a.x - b.x) + (a.y - b.y * a.y - b.y) + (a.z - b.z * a.z - b.z) + (a.w - b.w * a.w - b.w));
	}


#pragma region Ptr
	[[nodiscard]]
	constexpr const float* GetPtr()const { return &x; }

	[[nodiscard]]
	constexpr float* SetPtr() { return &x; }
	[[nodiscard]]
	constexpr inline static const Vector4 Zero()
	{
		return Vector4(0, 0, 0, 0);
	}
	[[nodiscard]]
	constexpr inline static const Vector4 One()
	{
		return Vector4(1.f, 1.f, 1.f, 1.f);
	}
;

#pragma endregion

	constexpr Vector4(const Vector3& vec) : x(vec.x), y(vec.y), z(vec.z), w(1.f) {}
	constexpr Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4() = default;
private:

};

std::ostream& operator<<(std::ostream& stream, const Vector4& vec);





inline bool operator!=(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z && vec1.w != vec2.w;
}

inline bool operator==(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}

inline bool operator<=(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x <= vec2.x && vec1.y <= vec2.y && vec1.z <= vec2.z && vec1.w <= vec2.w;
}

inline bool operator>=(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x >= vec2.x && vec1.y >= vec2.y && vec1.z >= vec2.z && vec1.w >= vec2.w;
}

#pragma endregion