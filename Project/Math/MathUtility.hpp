#pragma once

////////////////////////////////////////////////////////////
// Includes ////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include <math.h>

////////////////////////////////////////////////////////////
// Classes /////////////////////////////////////////////////
////////////////////////////////////////////////////////////

class MathUtility
{
private:

	MathUtility() {}
	~MathUtility() {}

public:

	inline static float Max(float a, float b)
	{
		return (a > b ? a : b);
	}

	inline static float Max(float a, float b, float c)
	{
		return Max(a, Max(b, c));
	}

	inline static float Min(float a, float b)
	{
		return (a < b ? a : b);
	}

	inline static float Min(float a, float b, float c)
	{
		return Min(a, Min(b, c));
	}

	inline static float Clamp(float x, float minValue, float maxValue)
	{
		return Min(maxValue, Max(minValue, x));
	}

	inline static float Saturate(float x)
	{
		return Clamp(x, 0.0f, 1.0f);
	}

	inline static float Lerp(float startValue, float endValue, float x)
	{
		x = Saturate(x);
		return startValue + (endValue - startValue) * x;
	}

	inline static float Smoothstep(float startValue, float endValue, float x)
	{
		float a = Saturate((x - startValue) / (endValue - startValue));
		return a * a * 3.0f - a * a * 2.0f;
	}

	inline static float RadianToAngle(float radian)
	{
		return radian / PI * 180.0f;
	}

	inline static float AngleToRadian(float angle)
	{
		return angle / 180.0f * PI;
	}

public:

	static const float PI;
};

const float MathUtility::PI = 3.141592653f;