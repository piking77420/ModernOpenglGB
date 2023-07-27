#pragma once
#include <iostream>
#include <cassert>

class Vector;
class Vector3;
class Vector4;

class Vector2 
{
public:


#pragma region Value
	float x = 0;
	float y = 0;
#pragma endregion
	constexpr static int Size()
	{
		return 2;
	}
#pragma region Function
	/**
	* @fn constexpr inline float Norm() const;
	* @brief This function calculates the norm of the vector
	* @return The norm of the vector.
	*/
	[[nodiscard]]
	constexpr inline float Norm() const;
	/**
	* @fn constexpr inline Vector2 Normalize() const
	* @brief This function calculates The vector normalize
	* @return The normalize vector.
	*/
	[[nodiscard]]
	constexpr inline Vector2 Normalize() const
	{
		float magnitude = Norm();

		if (magnitude == 1)
			return *this;

		return Vector2(float(x / magnitude), float(y / magnitude));
	}
	/**
	* @fn constexpr inline static float DotProduct(const Vector3& vec1, const Vector3& vec2) noexcept
	* @brief This fonction does the dot product of Vec1 and Vec2.
	* @return The dotProduct.
	*/
	[[nodiscard]]
	constexpr inline static float DotProduct(const Vector2 vec1, const Vector2 Row1)
	{
		return vec1.x * Row1.x + vec1.y * Row1.y;
	}
	/**
	* @fn constexpr inline Vector2 Normal() const 
	* @brief This fonction Return the Normal of the vector.
	* @return The Normal Vector.
	*/
	[[nodiscard]]
	constexpr inline Vector2 Normal() const 
	{
		return Vector2(y, -x).Normalize();
	}
	// Return CrossProduct
	[[nodiscard]]
	float CrossProduct(const Vector2 vec1, const Vector2 vec2) const;
	// Return Angle between 2 vectors
	[[nodiscard]]
	static float Angle(const Vector2 vec1, const Vector2 Row1) ;
	// Return Trigonametrial angle Cos(x) and sin(Y)
	[[nodiscard]]
	float Angle() const;
	//Return Determiant
	[[nodiscard]]
	constexpr static float Determinant(const Vector2 vec1, const Vector2 vec2)
	{
		return (vec1.x * vec2.y) - (vec1.y * vec2.x);
	}

	// Return Distance from 2 Vector without std::sqrtf;
	[[nodiscard]]
	constexpr static inline float DistanceSquare(Vector2 a, Vector2 b)
	{
		return ((a.x - b.x * a.x - b.x) + (a.y - b.y * a.y - b.y));
	}
	// Return Distance from 2 Vector
	[[nodiscard]]
	static float Distance(Vector2 a, Vector2 b);
	

	// Return the address of the first value;
	[[nodiscard]]
	constexpr float* SetPtr() 
	{
		return &x;
	}
	// Return the address of the first value;
	[[nodiscard]]
	constexpr const float* GetPtr() const 
	{
		return &x;
	}

	/**
	* \name Basic Value Constants
	* @{
	*/

	/**
	* @brief Return Vector2(0.f, 0.f)
	*/
	constexpr inline static const Vector2 Zero()
	{
		return Vector2(0.f, 0.f);
	}

	/**
	* @brief Return Vector2(1.f, 1.f)
	*/
	constexpr inline static const Vector2 One()
	{
		return Vector2(1.f, 1.f);
	}

	/**
	* @brief Return Vector2(1.f, 0.f)
	*/
	constexpr inline static const Vector2 Right()
	{
		return Vector2(1.f, 0.f);
	}

	/**
	* @brief Return Vector2(-1.f, 0.f)
	*/
	constexpr inline static const Vector2 Left()
	{
		return Vector2(-1.f, 0.f);
	}

	/**
	 * @brief Return Vector2(0.f, 1.f)
	 */
	constexpr inline static const Vector2 Up()
	{
		return Vector2(0.f, 1.f);
	}

	/**
	 * @brief Return Vector2(0.f, -1.f)
	 */
	constexpr inline static const Vector2 Down()
	{
		return Vector2(0.f, -1.f);
	}

	
	/** @} */ // End of Basic Value Constants

#pragma endregion 
	constexpr Vector2(float _x, float _y) : x(_x), y(_y)
	{
	}
	constexpr Vector2() = default;

	explicit operator Vector() const;
	explicit operator Vector3() const;
	explicit operator Vector4() const;

	constexpr float operator[](int i) const {
		assert(i >= 0 && i < 2);
		[[assume(i >= 0 && i < 2)]]

		if (i == 0)
			return x;

		if (i == 1)
			return y;
	}
	constexpr float& operator[](int i)
	{
		assert(i >= 0 && i < 2);
		[[assume(i >= 0 && i < 2)]]

		if (i == 0)
			return x;
		if (i == 1)
			return y;
	}



};



#pragma region Operator

constexpr inline Vector2 operator+(const Vector2 vec1, const Vector2 Row1)
{
	return Vector2(vec1.x + Row1.x, vec1.y + Row1.y);
}

constexpr inline Vector2 operator-(const Vector2 vec1, const Vector2 Row1)
{
	return Vector2(vec1.x - Row1.x, vec1.y - Row1.y);
}

constexpr inline Vector2 operator*(const Vector2 vec1, const Vector2 Row1)
{
	return Vector2(vec1.x * Row1.x, vec1.y * Row1.y);
}

constexpr inline Vector2 operator/(const Vector2 vec1, const Vector2 Row1)
{
	return Vector2(vec1.x / Row1.x, vec1.y / Row1.y);
}


constexpr inline Vector2 operator+(const Vector2 vec1, const float& value)
{
	Vector2 result = vec1;
	result.x += value;
	result.y += value;
	return result;
}

constexpr inline Vector2 operator*(const Vector2 vec1, const float& value)
{
	Vector2 result = vec1;
	result.x *= value;
	result.y *= value;
	return result;
}

constexpr inline Vector2 operator/(const Vector2 vec1, const float& value)
{
	Vector2 result = vec1;
	result.x /= value;
	result.y /= value;
	return result;
}

constexpr inline Vector2 operator-(const Vector2 vec1, const float& value)
{
	Vector2 result = vec1;
	result.x -= value;
	result.y -= value;
	return result;
}


constexpr inline void operator+=(Vector2& vec1, Vector2 Row1)
{
	vec1.x += Row1.x;
	vec1.y += Row1.y;
}

constexpr inline void operator-=(Vector2& vec1, Vector2 Row1)
{
	vec1.x -= Row1.x;
	vec1.y -= Row1.y;
}


constexpr inline void operator*=(Vector2& vec1, Vector2 Row1)
{
	vec1.x *= Row1.x;
	vec1.y *= Row1.y;
}

constexpr inline void operator/=(Vector2& vec1, Vector2 Row1)
{
	vec1.x /= Row1.x;
	vec1.y /= Row1.y;
}


#pragma endregion


std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

constexpr inline bool operator!=(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x != vec2.x && vec1.y != vec2.y;
}

constexpr inline bool operator==(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

constexpr inline bool operator<=(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x <= vec2.x && vec1.y <= vec2.y;
}

constexpr inline bool operator>=(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x >= vec2.x && vec1.y >= vec2.y;
}