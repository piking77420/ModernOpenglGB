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
	// Return Norm of a Vector
	[[nodiscard]]
	constexpr inline float Norm() const;
	// return Normaize one Vector
	[[nodiscard]]
	constexpr inline Vector2 Normalize() const
	{
		float magnitude = Norm();

		if (magnitude == 1)
			return *this;

		return Vector2(float(x / magnitude), float(y / magnitude));
	}
	// Return the dot product
	[[nodiscard]]
	constexpr inline static float DotProduct(const Vector2& vec1, const Vector2& Row1)
	{
		return vec1.x * Row1.x + vec1.y * Row1.y;
	}
	// Return the Normal of a Vector
	[[nodiscard]]
	Vector2 Normal() const;
	// Return CrossProduct
	[[nodiscard]]
	float CrossProduct(const Vector2& vec1, const Vector2& vec2) const;
	// Return Angle between 2 vectors
	[[nodiscard]]
	static float Angle(const Vector2& vec1, const Vector2& Row1) ;
	// Return Trigonametrial angle Cos(x) and sin(Y)
	[[nodiscard]]
	float Angle() const;
	//Return Determiant
	[[nodiscard]]
	constexpr static float Determinant(const Vector2& vec1, const Vector2& vec2)
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
	float* SetPtr();
	// Return the address of the first value;
	[[nodiscard]]
	const float* GetPtr() const;



	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Left;
	static const Vector2 Up;
	static const Vector2 Down;

#pragma endregion 
	Vector2(float x, float y) ; 
	Vector2() = default;

	explicit operator Vector() const;
	explicit operator Vector3() const;
	explicit operator Vector4() const;

	float operator[](int i) const;
	float& operator[](int i);


private:

};



#pragma region Operator

 inline Vector2 operator+(const Vector2& vec1, const Vector2& Row1)
{
	return Vector2(vec1.x + Row1.x, vec1.y + Row1.y);
}

 inline Vector2 operator-(const Vector2& vec1, const Vector2& Row1)
{
	return Vector2(vec1.x - Row1.x, vec1.y - Row1.y);
}

 inline Vector2 operator*(const Vector2& vec1, const Vector2& Row1)
{
	return Vector2(vec1.x * Row1.x, vec1.y * Row1.y);
}

 inline Vector2 operator/(const Vector2& vec1, const Vector2& Row1)
{
	return Vector2(vec1.x / Row1.x, vec1.y / Row1.y);
}


 inline Vector2 operator+(const Vector2& vec1, const float& value)
 {
	 Vector2 result = vec1;
	 result.x += value;
	 result.y += value;
	 return result;
 }

 inline Vector2 operator*(const Vector2& vec1, const float& value)
 {
	 Vector2 result = vec1;
	 result.x *= value;
	 result.y *= value;
	 return result;
 }

 inline Vector2 operator/(const Vector2& vec1, const float& value)
 {
	 Vector2 result = vec1;
	 result.x /= value;
	 result.y /= value;
	 return result;
 }

 inline Vector2 operator-(const Vector2& vec1, const float& value)
 {
	 Vector2 result = vec1;
	 result.x -= value;
	 result.y -= value;
	 return result;
 }


 inline void operator+=(Vector2& vec1 , Vector2 Row1)
{
	vec1.x += Row1.x;
	vec1.y += Row1.y;
}

 inline void operator-=(Vector2& vec1, Vector2 Row1)
{
	vec1.x -= Row1.x;
	vec1.y -= Row1.y;
}


 inline void operator*=(Vector2& vec1, Vector2 Row1)
{
	vec1.x *= Row1.x;
	vec1.y *= Row1.y;
}

 inline void operator/=(Vector2& vec1, Vector2 Row1)
{
	vec1.x /= Row1.x;
	vec1.y /= Row1.y;
}


#pragma endregion


std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

inline bool operator!=(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x != vec2.x && vec1.y != vec2.y;
}

inline bool operator==(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

inline bool operator<=(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x <= vec2.x && vec1.y <= vec2.y;
}

inline bool operator>=(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x >= vec2.x && vec1.y >= vec2.y;
}