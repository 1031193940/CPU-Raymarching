#pragma once

////////////////////////////////////////////////////////////
// Includes ////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include <math.h>

////////////////////////////////////////////////////////////
// Classes /////////////////////////////////////////////////
////////////////////////////////////////////////////////////

class Vector2f
{
public:
	Vector2f() : x(0.0f), y(0.0f) {}
	Vector2f(float _a) : x(_a), y(_a) {}
	Vector2f(float _x, float _y) : x(_x), y(_y) {}
	Vector2f(const Vector2f& other) : x(other.x), y(other.y) {}

	inline Vector2f operator+() const { return *this; }
	inline Vector2f operator-() const { return Vector2f(-x, -y); }
	inline Vector2f operator+(const Vector2f& other) const { return Vector2f(x + other.x, y + other.y); }
	inline Vector2f operator-(const Vector2f& other) const { return Vector2f(x - other.x, y - other.y); }
	inline Vector2f operator*(const Vector2f& other) const { return Vector2f(x * other.x, y * other.y); }
	inline Vector2f operator/(const Vector2f& other) const { return Vector2f(x / other.x, y / other.y); }
	inline Vector2f operator+(const float scaler) const { return Vector2f(x + scaler, y + scaler); }
	inline Vector2f operator-(const float scaler) const { return Vector2f(x - scaler, y - scaler); }
	inline Vector2f operator*(const float scaler) const { return Vector2f(x * scaler, y * scaler); }
	inline Vector2f operator/(const float scaler) const { return Vector2f(x / scaler, y / scaler); }

	inline Vector2f& operator=(const Vector2f& other) { x = other.x; y = other.y; return *this; }

	inline Vector2f& operator+=(const Vector2f& other) { x += other.x; y += other.y; return *this; }
	inline Vector2f& operator-=(const Vector2f& other) { x -= other.x; y -= other.y; return *this; }
	inline Vector2f& operator*=(const Vector2f& other) { x *= other.x; y *= other.y; return *this; }
	inline Vector2f& operator/=(const Vector2f& other) { x /= other.x; y /= other.y; return *this; }
	inline Vector2f& operator-=(const float scaler) { x -= scaler; y -= scaler; return *this; }
	inline Vector2f& operator+=(const float scaler) { x += scaler; y += scaler; return *this; }
	inline Vector2f& operator*=(const float scaler) { x *= scaler; y *= scaler; return *this; }
	inline Vector2f& operator/=(const float scaler) { x /= scaler; y /= scaler; return *this; }

	inline bool operator==(const Vector2f& other) const { return (x == other.x && y == other.y); }
	inline bool operator!=(const Vector2f& other) const { return (x != other.x || y != other.y); }

	inline float& operator[](int i) { return (&x)[i]; }

public:

	inline static Vector2f Abs(const Vector2f& vec)
	{
		return Vector2f(abs(vec.x), abs(vec.y));
	}

	inline static float Dot(const Vector2f& vec1, const Vector2f& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	inline static float Length(const Vector2f& vec)
	{
		return sqrt(Dot(vec, vec));
	}

	inline static float Distance(const Vector2f& vec1, const Vector2f& vec2)
	{
		Vector2f componentsDistance = vec1 - vec2;
		return sqrt(Dot(componentsDistance, componentsDistance));
	}

	inline static Vector2f Normalize(const Vector2f& vec)
	{
		return vec / Length(vec);
	}

	inline static Vector2f Max(const Vector2f& vec1, const Vector2f& vec2)
	{
		return Vector2f
		(
			Max(vec1.x, vec2.x),
			Max(vec1.y, vec2.y)
		);
	}

	inline static Vector2f Min(const Vector2f& vec1, const Vector2f& vec2)
	{
		return Vector2f
		(
			Min(vec1.x, vec2.x),
			Min(vec1.y, vec2.y)
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

	static const Vector2f Zero;
	static const Vector2f One;

public:

	float x, y;
};

const Vector2f Vector2f::Zero = Vector2f(0.0f, 0.0f);

const Vector2f Vector2f::One = Vector2f(1.0f, 1.0f);
