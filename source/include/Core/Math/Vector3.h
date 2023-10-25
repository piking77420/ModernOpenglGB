 

#pragma once
#include "Vector2.h"
#include "Mathf.h"
class Vector;
class Vector4;

/**
	*@class Vector3
	*@brief vector of 3 dimension
	*/




class Vector3
{
public:

	/**
	* @var x 
	X value of the class
	*/
	float x = 0.f;
	/**
	* @var y
	Y value of the class
	*/
	float y = 0.f;
	/**
	* @var z
	Z value of the class
	*/
	float z = 0.f;

	/**
		* @fn constexpr static uint16_t Size();
		* @brief This function Return the size of the vector.
		* @return the size of the vector.
		*/
	constexpr static uint16_t Size()
	{
		return 3;
	}




	/**
	 * @fn inline float Norm() const
	 * @brief This function calculates the norm of the vector.
	 *
	 * <img src="vector3Norm.png" alt="Vector3 Norm" style="float: left; margin-right: 10px;" />
	 * <br> <!-- Line break -->
	 * <br> <!-- Line break -->
	 * <br> <!-- Line break -->
	 *
	 * @return The norm of the vector.
	 */
	[[nodiscard]]
	inline float Norm() const;

	
	/**
	* @fn line Vector3 Normalize() const
	* @brief This fonction Normalize a copy of the Vector.
	* @return The NormalizeVector.
	*/
	[[nodiscard]]
	 Vector3 Normalize() const;
	

	 /**
	 * @fn constexpr inline float FNorm() const;
	 * @brief This function calculates the norm of the vector with The Math::FSqrtf.
	 * @return The norm of the vector.
	 */
	 [[nodiscard]]
	 constexpr inline float FNorm() const
	 {
		 return (float)Math::FSqrtf((x * x) + (y * y) + (z * z));
	 }
	 /**
	 * @fn line Vector3 Normalize() const
	 * @brief This fonction Normalize a copy of the Vector with FNorm fn.
	 * @return The NormalizeVector.
	 */
	 [[nodiscard]]
	 constexpr inline Vector3 FNormalize() const
	 {
		 float norm = FNorm();


		 return Vector3(x / norm, y / norm, z / norm);
	 }

	/**
	* @fn Vector3 Reflect(const Vector3& Vector, const Vector3& Normals)
	* @brief This fonction Calculate the Reflect vector of a vector and a normal vector.
	* @param Vector the BaseVector
	* @param vec2 the NormalVector
	* @return The ReflectVector.
	*/ [[nodiscard]]
	static Vector3 Reflect(const Vector3& Vector, const Vector3& Normal);

	/**
	* @fn constexpr inline static float DotProduct(const Vector3& vec1, const Vector3& vec2) noexcept
	* @brief This fonction does the dot product of Vec1 and Vec2.
	* @return The dotProduct.
	*/
	[[nodiscard]]
	constexpr inline static float DotProduct(const Vector3& vec1, const Vector3& vec2) noexcept
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}
	
	/**
	* @fn constexpr inline static Vector3 CrossProduct(const Vector3& vec1, const Vector3& vec2) noexcept
	* @brief This fonction does the cross product between the Vec1 and the Vec2.
	* @return The CrosProduct.
	*/
	[[nodiscard]]
	constexpr inline static Vector3 CrossProduct(const Vector3& vec1, const Vector3& vec2) noexcept
	{
		return Vector3(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x);
	}

	/**
	* @fn inline static float Angle(const Vector3& vec1, const Vector3& Row1)
	* @brief This function Calculate the angle between 2 vector.
	* @return The angle between 2 vector.
	*/ 
	[[nodiscard]]
	inline static float Angle(const Vector3& vec1, const Vector3& Row1)
	{
		return std::acosf(Vector3::DotProduct(vec1, Row1) / (vec1.Norm() * Row1.Norm()));
	}

	/**
	* @fn constexpr static inline float DistanceSquare(const Vector3& a, const Vector3& b)
	* @brief This function Calculate the Distance between 2 point without using a sqrtf function.
	* @return The DistanceSquare of 2 point.
	*/
	[[nodiscard]]
	constexpr static inline float DistanceSquare(const Vector3& a, const Vector3& b)
	{
		const float dx = a.x - b.x;
		const float dy = a.y - b.y;
		const float dz = a.z - b.z;
		const float result = (dx * dx + dy * dy + dz * dz);

		return result;
	}
	/**
	* @fn constexpr static inline float Distance(const Vector3& a, const Vector3& b)
	* @brief This function Calculate the Distance between 2 point.
	* @return The DistanceSquare of 2 point.
	*/
	[[nodiscard]]
	static inline float Distance(const Vector3& a, const Vector3& b)
	{
		const float dx = a.x - b.x;
		const float dy = a.y - b.y;
		const float dz = a.z - b.z;
		const float result = std::sqrt(dx * dx + dy * dy + dz * dz);
		return result;
	}



	static inline Vector3 scale(const Vector3& v, float desiredLength)
	{
		return v * desiredLength / v.Norm();
	}

	
	/**
	* @fn constexpr float* SetPtr()
	* @brief This function Return a pointer to the adress of the vector
	*/
	constexpr float* SetPtr() { return &x; } 
	/**
	* @fn constexpr float* GetPtr()
	* @brief This function Return a pointer to the adress of the vector
	* @warning With const you can't modify the value for this use SetPtr instead
	*/
	constexpr const float* GetPtr() const { return &x; }

	[[nodiscard]]
	Vector3 MakePositivEuleur() const;

	/*
	[[nodiscard]]
	static inline Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t)
	{
		float phi = std::acos(Vector3::DotProduct(v1, v2));
		float valueP0 = std::sin((1 - t) * phi) / std::sin(phi);
		float valueP1 = std::sin(t * phi) / std::sin(phi);


		return  (v1 * valueP0) + (v2 * valueP1);
	}
	*/
	/**
	* \name Basic Value Constants
	* @{
	*/

	/**
	 * @brief Return Vector(0,0,0)
	 */
	constexpr inline static Vector3 Zero() noexcept
	{
		return Vector3(0, 0, 0);
	}

	/**
	 * @brief Return Vector(1,1,1)
	 */
	constexpr inline static  Vector3 One() noexcept
	{
		return Vector3(1, 1, 1);
	}

	/**
	 * @brief Return Vector(1,0,0)
	 */
	constexpr inline static  Vector3 Right() noexcept
	{
		return Vector3(1.f, 0.f, 0.f);
	}

	/**
	 * @brief Return Vector(-1,0,0)
	 */
	constexpr inline static  Vector3 Left() noexcept
	{
		return Vector3(-1.f, 0.f, 0.f);
	}

	/**
	 * @brief Return Vector(0,1,0)
	 */
	constexpr inline static  Vector3 Up() noexcept
	{
		return Vector3(0.f, 1.f, 0.f);
	}

	/**
	 * @brief Return Vector(0,-1,0)
	 */
	constexpr inline static  Vector3 Down() noexcept
	{
		return Vector3(0.f, -1.f, 0.f);
	}

	/**
	 * @brief Return Vector(0,0,1)
	 */
	constexpr inline static  Vector3 Forward() noexcept
	{
		return Vector3(0.f, 0.f, 1.f);
	}

	/**
	 * @brief Return Vector(0,0,-1)
	 */
	constexpr inline static  Vector3 BackForward() noexcept
	{
		return Vector3(0.f, 0.f, -1.f);
	}

	/** @} */ // End of Basic Value Constants

	/**
	* \name Operator Overloads
	* @{
	*/

	/**
	* @brief Overloaded subscript operator for const objects.
	* @param i The index.
	* @return The value at the given index.
	*/
	constexpr float operator[](int i) const
	{
		return *static_cast<const float*>(&x + i);
	}

	/**
	 * @brief Overloaded subscript operator for non-const objects.
	 * @param i The index.
	 * @return The reference at the given index.
	 */
	constexpr float& operator[](int i)
	{
		return *static_cast<float*>(&x + i);
	}
	/** @} */ // End of Operator Overloads


	/**
	* \name Cast Operator 
	* @{
	*/

	/**
	 * @brief CastOperator of Vector2.
	 * @return Vector2(x,y).
	 */
	explicit operator Vector2() const;
	/**
	 * @brief CastOperators of Vector.
	 * @return Vector of size 3.
	 */
	explicit operator Vector() const;
	/**
	 * @brief CastOperator of Vector4.
	 * @return Vector4(x,y,z,0).
	 */
	explicit operator Vector4() const;


	/** @} */ // End of Cast Operator 

	Vector3 operator*(float value) const {
		return Vector3(x * value, y * value, z * value);
	}

	


	Vector3 operator/(float value) const {
		return Vector3(x / value, y / value, z / value);
	}

	/**
	* \name Constructor
	* @{
	*/
	/**
	 * @brief Constructor with 3 float for x y z value
	 */
	constexpr Vector3(float X, float Y, float Z) :  x(X), y(Y), z(Z)
	{
	}
	/**
	 * @brief Default Contructor x = 0 , y = 0 , z = 0 
	 */
	constexpr Vector3() = default;

	/** @} */ // End of Constructor



	constexpr inline Vector3 operator+(const Vector3& Row1) const noexcept
	{
		return Vector3(x + Row1.x, y + Row1.y, z + Row1.z);
	}
	constexpr inline Vector3 operator-(const Vector3& Row1) const noexcept
	{
		return Vector3(x - Row1.x, y - Row1.y, z - Row1.z);
	}

	constexpr inline Vector3 operator-() const noexcept
	{
		return Vector3(-x, -y, -z);
	}
	
	constexpr inline Vector3 operator*(const Vector3& Row1) const noexcept
	{
		return Vector3(x * Row1.x, y * Row1.y, z * Row1.z);
	}
	constexpr inline Vector3 operator/(const Vector3& Row1) const noexcept
	{
		return Vector3(x / Row1.x, y / Row1.y, z / Row1.z);
	}



	constexpr inline void operator+= ( const Vector3 Row1) noexcept
	{
		x += Row1.x;
		y += Row1.y;
		z += Row1.z;
	}
	constexpr inline void operator-= ( const Vector3 Row1) noexcept
	{
		x -= Row1.x;
		y -= Row1.y;
		z -= Row1.z;
	}
	constexpr inline void operator*= (const Vector3 Row1) noexcept
	{
		x *= Row1.x;
		y *= Row1.y;
		z *= Row1.z;
	}
	constexpr inline void operator/= (const Vector3 Row1) noexcept
	{
		x /= Row1.x;
		y /= Row1.y;
		z /= Row1.z;
	}


	constexpr inline Vector3 operator+(const float value) const noexcept
	{
		Vector3 result = *this;
		result.x += value;
		result.y += value;
		result.z += value;
		return result;
	}


	

	constexpr inline Vector3 operator-(const float value) const noexcept
	{
		Vector3 result = *this;
		result.x -= value;
		result.y -= value;
		result.z -= value;
		return result;
	}

	constexpr inline Vector3 operator*=(const float value) noexcept
	{
		Vector3 result = *this;
		result.x *= value;
		result.y *= value;
		result.z *= value;
		return result;
	}

};






std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
