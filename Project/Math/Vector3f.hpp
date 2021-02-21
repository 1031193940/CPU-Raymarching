#pragma once

////////////////////////////////////////////////////////////
// Includes ////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include <math.h>

////////////////////////////////////////////////////////////
// Classes /////////////////////////////////////////////////
////////////////////////////////////////////////////////////

class Vector3f
{
public:
	Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3f(float _a) : x(_a), y(_a), z(_a) {}
	Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3f(const Vector3f& other) : x(other.x), y(other.y), z(other.z) {}

	inline Vector3f operator+() const { return *this; }
	inline Vector3f operator-() const { return Vector3f(-x, -y, -z); }
	inline Vector3f operator+(const Vector3f& other) const { return Vector3f(x + other.x, y + other.y, z + other.z); }
	inline Vector3f operator-(const Vector3f& other) const { return Vector3f(x - other.x, y - other.y, z - other.z); }
	inline Vector3f operator*(const Vector3f& other) const { return Vector3f(x * other.x, y * other.y, z * other.z); }
	inline Vector3f operator/(const Vector3f& other) const { return Vector3f(x / other.x, y / other.y, z / other.z); }
	inline Vector3f operator+(const float scaler) const { return Vector3f(x + scaler, y + scaler, z + scaler); }
	inline Vector3f operator-(const float scaler) const { return Vector3f(x - scaler, y - scaler, z - scaler); }
	inline Vector3f operator*(const float scaler) const { return Vector3f(x * scaler, y * scaler, z * scaler); }
	inline Vector3f operator/(const float scaler) const { return Vector3f(x / scaler, y / scaler, z / scaler); }

	inline Vector3f& operator=(const Vector3f& other) { x = other.x; y = other.y; z = other.z; return *this; }

	inline Vector3f& operator+=(const Vector3f& other) { x += other.x; y += other.y; z += other.z; return *this; }
	inline Vector3f& operator-=(const Vector3f& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	inline Vector3f& operator*=(const Vector3f& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	inline Vector3f& operator/=(const Vector3f& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	inline Vector3f& operator-=(const float scaler) { x -= scaler; y -= scaler; z -= scaler; return *this; }
	inline Vector3f& operator+=(const float scaler) { x += scaler; y += scaler; z += scaler; return *this; }
	inline Vector3f& operator*=(const float scaler) { x *= scaler; y *= scaler; z *= scaler; return *this; }
	inline Vector3f& operator/=(const float scaler) { x /= scaler; y /= scaler; z /= scaler; return *this; }

	inline bool operator==(const Vector3f& other) const { return (x == other.x && y == other.y && z == other.z); }
	inline bool operator!=(const Vector3f& other) const { return (x != other.x || y != other.y || z != other.z); }

	inline float& operator[](int i) { return (&x)[i]; }

public:

	inline static Vector3f Abs(const Vector3f& vec)
	{
		return Vector3f(abs(vec.x), abs(vec.y), abs(vec.z));
	}

	inline static float Dot(const Vector3f& vec1, const Vector3f& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	inline static Vector3f Cross(const Vector3f& vec1, const Vector3f& vec2)
	{
		return Vector3f
		(
			vec1.y * vec2.z - vec2.y * vec1.z,
			vec2.x * vec1.z - vec1.x * vec2.z,
			vec1.x * vec2.y - vec2.x * vec1.y
		);
	}

	inline static float Length(const Vector3f& vec)
	{
		return sqrt(Dot(vec, vec));
	}

	inline static float Distance(const Vector3f& vec1, const Vector3f& vec2)
	{
		Vector3f componentsDistance = vec1 - vec2;
		return sqrt(Dot(componentsDistance, componentsDistance));
	}

	inline static Vector3f Normalize(const Vector3f& vec)
	{
		return vec / Length(vec);
	}

	inline static Vector3f Max(const Vector3f& vec1, const Vector3f& vec2)
	{
		return Vector3f
		(
			Max(vec1.x, vec2.x),
			Max(vec1.y, vec2.y),
			Max(vec1.z, vec2.z)
		);
	}

	inline static Vector3f Min(const Vector3f& vec1, const Vector3f& vec2)
	{
		return Vector3f
		(
			Min(vec1.x, vec2.x),
			Min(vec1.y, vec2.y),
			Min(vec1.z, vec2.z)
		);
	}

private:

	inline static float Max(float a, float b)
	{
		return (a > b ? a : b);
	}

	inline static float Min(float a, float b)
	{
		return (a < b ? a : b);
	}

public:

	static const Vector3f Zero;
	static const Vector3f One;
	static const Vector3f Up;
	static const Vector3f Right;
	static const Vector3f Forward;

public:

	float x, y, z;
};

const Vector3f Vector3f::Zero = Vector3f(0.0f, 0.0f, 0.0f);

const Vector3f Vector3f::One = Vector3f(1.0f, 1.0f, 1.0f);

const Vector3f Vector3f::Up = Vector3f(0.0f, 1.0f, 0.0f);

const Vector3f Vector3f::Right = Vector3f(1.0f, 0.0f, 0.0f);

const Vector3f Vector3f::Forward = Vector3f(0.0f, 0.0f, 1.0f);