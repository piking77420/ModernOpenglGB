#pragma once
#include "Vector2.h"

class Vector;
class Vector4;


class Vector3
{
public:

	float x = 0 ;
	float y = 0;
	float z = 0;


	constexpr static int Size()
	{
		return 3;
	}

	// Return the Norm of the Vector // 
	[[nodiscard]]
	constexpr inline float Norm() const;
	
	// Return the Normalize Vector// 
	[[nodiscard]]
	constexpr inline Vector3 Normalize() const
	{
		float norm = Norm();

		if (norm == 1.f)
			return *this;

		return Vector3(x / norm, y / norm, z / norm);
	}
	// Return the Reflect Vector// 
	[[nodiscard]]
	Vector3 Reflect(const Vector3& Vector, const Vector3& Normals);
	// Return the DotProduct Vector// 
	[[nodiscard]]
	inline static float DotProduct(const Vector3& vec1, const Vector3& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}
	// Return the CrossProduct Vector// 
	[[nodiscard]]
	inline static Vector3 CrossProduct(const Vector3& vec1, const Vector3& vec2)
	{

		return Vector3(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x);
	}

	// Return the angle from 2 vector// 
	[[nodiscard]]
	inline static float Angle(const Vector3& vec1, const Vector3& Row1)
	{
		return std::acosf(Vector3::DotProduct(vec1, Row1) / (vec1.Norm() * Row1.Norm()));
	}

	// Return Distance from 2 Vector without std::sqrtf;
	[[nodiscard]]
	constexpr static inline float DistanceSquare(const Vector3& a, const Vector3& b)
	{
		const float dx = a.x - b.x;
		const float dy = a.y - b.y;
		const float dz = a.z - b.z;
		const float result = (dx * dx + dy * dy + dz * dz);

		return result;
	}
	// Return Distance from 2 Vector
	[[nodiscard]]
	static inline float Distance(const Vector3& a, const Vector3& b)
	{
		const float dx = a.x - b.x;
		const float dy = a.y - b.y;
		const float dz = a.z - b.z;
		const float result = std::sqrtf(dx * dx + dy * dy + dz * dz);
		return result;
	}




	constexpr float* SetPtr() { return &x; }
	constexpr const float* GetPtr() const { return &x; }

	// Basic Values //

	// Return Vector(0,0,0) // 
	static const Vector3 Zero;
	// Return Vector(1,1,1) // 
	static const Vector3 One;
	// Return Vector(1,0,0) // 
	static const Vector3 Right;
	// Return Vector(-1,0,0) // 
	static const Vector3 Left;
	// Return Vector(0,1,0) // 
	static const Vector3 Up;
	// Return Vector(0,-1,0) // 
	static const Vector3 Down;
	// Return Vector(0,0,1) // 
	static const Vector3 Forward;
	// Return Vector(0,0,-1) // 
	static const Vector3 BackForward;


	float operator[](int i) const;
	float& operator[](int i);

	
	explicit operator Vector2() const;
	explicit operator Vector() const;
	explicit operator Vector4() const;
	

	Vector3(const Vector4& vec);
	Vector3(float _x, float _y, float _z);
	Vector3() = default;

private:




};





inline Vector3 operator+(const Vector3& vec1, const Vector3& Row1) noexcept
{
	return Vector3(vec1.x + Row1.x, vec1.y + Row1.y, vec1.z + Row1.z);
}
inline Vector3 operator-(const Vector3& vec1, const Vector3& Row1) noexcept
{
	return Vector3(vec1.x - Row1.x, vec1.y - Row1.y, vec1.z - Row1.z);
}
inline Vector3 operator-(const Vector3& vec) noexcept
{
	return Vector3(-vec.x, -vec.y, -vec.z);
}
inline Vector3 operator*(const Vector3& vec1, const Vector3& Row1) noexcept
{
	return Vector3(vec1.x * Row1.x, vec1.y * Row1.y, vec1.z * Row1.z);
}
inline Vector3 operator/(const Vector3& vec1, const Vector3& Row1) noexcept
{
	return Vector3(vec1.x / Row1.x, vec1.y / Row1.y, vec1.z / Row1.z);
}

inline void operator+= (Vector3& vec1, const Vector3 Row1) noexcept
{
	vec1.x += Row1.x;
	vec1.y += Row1.y;
	vec1.z += Row1.z;
}
inline void operator-= (Vector3& vec1, const Vector3 Row1) noexcept
{
	vec1.x -= Row1.x;
	vec1.y -= Row1.y;
	vec1.z -= Row1.z;
}
inline void operator*= (Vector3& vec1, const Vector3 Row1) noexcept
{
	vec1.x *= Row1.x;
	vec1.y *= Row1.y;
	vec1.z *= Row1.z;
}
inline void operator/= (Vector3& vec1, const Vector3 Row1) noexcept
{
	vec1.x /= Row1.x;
	vec1.y /= Row1.y;
	vec1.z /= Row1.z;
}
inline Vector3 operator+(const Vector3& vec1, const float value) noexcept 
{
	Vector3 result = vec1;
	result.x += value;
	result.y += value;
	result.z += value;
	return result;
}
inline Vector3 operator*(const Vector3& vec1, const float value) noexcept
{
	Vector3 result = vec1;
	result.x *= value;
	result.y *= value;
	result.z *= value;
	return result;
}

inline Vector3 operator*(const float value, const Vector3& vec1) noexcept
{
	Vector3 result = vec1;
	result.x *= value;
	result.y *= value;
	result.z *= value;
	return result;
}
inline Vector3 operator/(const Vector3& vec1, const float value) noexcept
{
	Vector3 result = vec1;
	result.x /= value;
	result.y /= value;
	result.z /= value;
	return result;
}
inline Vector3 operator-(const Vector3& vec1, const float value) noexcept
{
	Vector3 result = vec1;
	result.x -= value;
	result.y -= value;
	result.z -= value;
	return result;
}

inline Vector3 operator*=(const Vector3& vec1, const float value) noexcept
{
	Vector3 result = vec1;
	result.x *= value;
	result.y *= value;
	result.z *= value;
	return result;
}

inline bool operator!=(const Vector3& vec1, const Vector3& vec2) noexcept
{
	return (vec1.x != vec2.x) || (vec1.y != vec2.y) || (vec1.z != vec2.z);
}

inline bool operator==(const Vector3& vec1, const Vector3& vec2) noexcept
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

inline bool operator<=(const Vector3& vec1, const Vector3& vec2) noexcept
{
	return vec1.x <= vec2.x && vec1.y <= vec2.y && vec1.z <= vec2.z;
}

inline bool operator<(const Vector3& vec1, const Vector3& vec2) noexcept
{
	return vec1.x < vec2.x&& vec1.y < vec2.y&& vec1.z < vec2.z;
}

inline bool operator>(const Vector3& vec1, const Vector3& vec2) noexcept
{
	return vec1.x > vec2.x && vec1.y > vec2.y && vec1.z > vec2.z;
}

inline bool operator>=(const Vector3& vec1, const Vector3& vec2) noexcept
{
	return vec1.x >= vec2.x && vec1.y >= vec2.y && vec1.z >= vec2.z;
}

inline Vector3 operator/(const float value, const Vector3& Row1) noexcept
{
	return Vector3(value / Row1.x, value / Row1.y, value / Row1.z);
}


inline void operator+= (Vector3& vec1, const Vector2 Row1) noexcept
{
	vec1.x += Row1.x;
	vec1.y += Row1.y;
}
inline void operator-= (Vector3& vec1, const Vector2 Row1) noexcept
{
	vec1.x -= Row1.x;
	vec1.y -= Row1.y;
}

inline void operator*= (Vector3& vec1, const Vector2 Row1) noexcept
{
	vec1.x *= Row1.x;
	vec1.y *= Row1.y;
}
inline void operator/= (Vector3& vec1, const Vector2 Row1) noexcept
{
	vec1.x /= Row1.x;
	vec1.y /= Row1.y;
}


std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
