#pragma once
#include <iostream>


class Vector;
class Vector3;

class Vector2 
{
public:


#pragma region Value
	float x;
	float y;
#pragma endregion


#pragma region Function
	[[nodiscard]]
	// Return Norm of a Vector
	float Norm() const;
	[[nodiscard]]
	// return Normaize one Vector
	Vector2 Normalize() const;
	// Return the dot product
	float DotProduct(const Vector2& Row0) const ;
	// Return the dot product
	float DotProduct(const Vector2& vec1, const Vector2& Row1) const;
	// Return the Normal of a Vector
	Vector2 Normal() const;
	// Return Determinant
	float Determinant(const Vector2& Row0) const;
	// Return CrossProduct
	float CrossProduct(const Vector2& Row0) const; 
	// Return Angle between 2 vectors
	float Angle(const Vector2& vec1, const Vector2& Row1) const;
	// Return Trigonametrial angle Cos(x) and sin(Y)
	float Angle() const;
	//Return Determiant
	float Determinant(const Vector2& vec1, const Vector2& Row1) const;




	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Left;
	static const Vector2 Up;
	static const Vector2 Down;




#pragma region Rotation

	Vector2 Rotation(const float cos, const float sin) const;

	Vector2 Rotate(const Vector2 center, const float cos, const float sin) const;

	Vector2 Rotate(const float angle, const Vector2 center) const;



#pragma endregion 



		
#pragma endregion 
	Vector2(float x, float y) ; 
	Vector2();
	~Vector2();

	explicit operator Vector() const;
	explicit operator Vector3() const;


	// Mettre dans vector3
	// explicite operator vector
	// inplicte a regader
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