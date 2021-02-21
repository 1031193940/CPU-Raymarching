#pragma once

class Color3f
{
public:

	Color3f() : r(0.0f), g(0.0f), b(0.0f)
	{
		// DO NOTHING
	}

	Color3f(float v) : r(v), g(v), b(v)
	{
		// DO NOTHING
	}

	Color3f(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{
		// DO NOTHING
	}

	Color3f(const Color3f& other) : r(other.r), g(other.g), b(other.b)
	{
		// DO NOTHING
	}

public:

	inline Color3f& operator=(float v) { r = v; g = v; b = v; return *this; }
	inline Color3f& operator=(const Color3f& other) { r = other.r; g = other.g; b = other.b; return *this; }

	inline bool operator==(const Color3f& other) const { return (r == other.r && g == other.g && b == other.b); }
	inline bool operator!=(const Color3f& other) const { return (r != other.r || g != other.g || b != other.b); }

	inline Color3f operator+(float v) const { return Color3f(r + v, g + v, b + v); }
	inline Color3f operator-(float v) const { return Color3f(r - v, g - v, b - v); }
	inline Color3f operator*(float v) const { return Color3f(r * v, g * v, b * v); }
	inline Color3f operator/(float v) const { return Color3f(r / v, g / v, b / v); }
	inline Color3f operator+(const Color3f& other) const { return Color3f(r + other.r, g + other.g, b + other.b); }
	inline Color3f operator-(const Color3f& other) const { return Color3f(r - other.r, g - other.g, b - other.b); }
	inline Color3f operator*(const Color3f& other) const { return Color3f(r * other.r, g * other.g, b * other.b); }
	inline Color3f operator/(const Color3f& other) const { return Color3f(r / other.r, g / other.g, b / other.b); }

	inline Color3f& operator+=(float v) { r += v; g += v; b += v; return *this; }
	inline Color3f& operator-=(float v) { r -= v; g -= v; b -= v; return *this; }
	inline Color3f& operator*=(float v) { r *= v; g *= v; b *= v; return *this; }
	inline Color3f& operator/=(float v) { r /= v; g /= v; b /= v; return *this; }
	inline Color3f& operator+=(const Color3f& other) { r += other.r; g += other.g; b += other.b; return *this; }
	inline Color3f& operator-=(const Color3f& other) { r -= other.r; g -= other.g; b -= other.b; return *this; }
	inline Color3f& operator*=(const Color3f& other) { r *= other.r; g *= other.g; b *= other.b; return *this; }
	inline Color3f& operator/=(const Color3f& other) { r /= other.r; g /= other.g; b /= other.b; return *this; }

public:

	float r, g, b;

public:

	static const Color3f Zero;
	static const Color3f One;
	static const Color3f Black;
	static const Color3f White;
	static const Color3f Red;
	static const Color3f Green;
	static const Color3f Blue;

};

const Color3f Color3f::Zero  = Color3f(0.0f, 0.0f, 0.0f);
const Color3f Color3f::One   = Color3f(1.0f, 1.0f, 1.0f);
const Color3f Color3f::Black = Color3f(0.0f, 0.0f, 0.0f);
const Color3f Color3f::White = Color3f(1.0f, 1.0f, 1.0f);
const Color3f Color3f::Red   = Color3f(1.0f, 0.0f, 0.0f);
const Color3f Color3f::Green = Color3f(0.0f, 1.0f, 0.0f);
const Color3f Color3f::Blue  = Color3f(0.0f, 0.0f, 1.0f);