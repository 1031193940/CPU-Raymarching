#pragma once


////////////////////////////////////////////////////////////
// Includes ////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include "Vector3f.hpp"
#include "MathUtility.hpp"

////////////////////////////////////////////////////////////
// Classes /////////////////////////////////////////////////
////////////////////////////////////////////////////////////

class Matrix3x3
{
public:

	Matrix3x3() : c0(Vector3f::Zero), c1(Vector3f::Zero), c2(Vector3f::Zero)
	{
		// DO NOTHING
	}

	Matrix3x3(const Vector3f& right, const Vector3f& up, const Vector3f& forward) : c0(right), c1(up), c2(forward)
	{
		// DO NOTHING
	}

	Matrix3x3(const Matrix3x3& other) : c0(other.c0), c1(other.c1), c2(other.c2)
	{
		// DO NOTHING
	}

	~Matrix3x3()
	{
		// DO NOTHING
	}

public:

	inline Matrix3x3& operator=(const Matrix3x3& other) { c0 = other.c0; c1 = other.c1; c2 = other.c2; return *this; }

	inline bool operator==(const Matrix3x3& other) const { return (c0 == other.c0 && c1 == other.c1 && c2 == other.c2); }
	inline bool operator!=(const Matrix3x3& other) const { return (c0 != other.c0 || c1 != other.c1 || c2 != other.c2); }

	inline float& operator()(int row, int col)
	{
		Vector3f* vec[3] = { &c0, &c1, &c2 };
		return (*vec[col])[row];
	}

	inline Matrix3x3 operator*(const float scaler) const
	{
		return Matrix3x3(c0 * scaler, c1 * scaler, c2 * scaler);
	}

	inline Matrix3x3 operator*(const Matrix3x3& other) const
	{
		Vector3f r0 = Vector3f(c0.x, c1.x, c2.x);
		Vector3f r1 = Vector3f(c0.y, c1.y, c2.y);
		Vector3f r2 = Vector3f(c0.z, c1.z, c2.z);

		return Matrix3x3
		(
			Vector3f(Vector3f::Dot(r0, other.c0), Vector3f::Dot(r0, other.c1), Vector3f::Dot(r0, other.c2)),
			Vector3f(Vector3f::Dot(r1, other.c0), Vector3f::Dot(r1, other.c1), Vector3f::Dot(r1, other.c2)),
			Vector3f(Vector3f::Dot(r2, other.c0), Vector3f::Dot(r2, other.c1), Vector3f::Dot(r2, other.c2))
		);
	}

	inline Matrix3x3& operator*=(const float scaler)
	{
		c0 *= scaler;
		c1 *= scaler;
		c2 *= scaler;
		return *this;
	}

	inline Matrix3x3& operator*=(const Matrix3x3& other)
	{
		Vector3f r0 = Vector3f(c0.x, c1.x, c2.x);
		Vector3f r1 = Vector3f(c0.y, c1.y, c2.y);
		Vector3f r2 = Vector3f(c0.z, c1.z, c2.z);

		c0 = Vector3f(Vector3f::Dot(r0, c0), Vector3f::Dot(r0, c1), Vector3f::Dot(r0, c2));
		c1 = Vector3f(Vector3f::Dot(r1, c0), Vector3f::Dot(r1, c1), Vector3f::Dot(r1, c2));
		c2 = Vector3f(Vector3f::Dot(r2, c0), Vector3f::Dot(r2, c1), Vector3f::Dot(r2, c2));

		return *this;
	}

public:

	static Matrix3x3 Scale(float sx, float sy, float sz)
	{
		return Matrix3x3
		(
			Vector3f(sx, 0.0f, 0.0f),
			Vector3f(0.0f, sy, 0.0f),
			Vector3f(0.0f, 0.0f, sz)
		);
	}

	static Matrix3x3 RotateX(float radian)
	{
		float sinTheta = sin(radian);
		float cosTheta = cos(radian);
		return RotateX(sinTheta, cosTheta);
	}

	static Matrix3x3 RotateX(float sinTheta, float cosTheta)
	{
		return Matrix3x3
		(
			Vector3f(1.0f, 0.0f, 0.0f),
			Vector3f(0.0f, cosTheta, -sinTheta),
			Vector3f(0.0f, sinTheta, cosTheta)
		);
	}

	static Matrix3x3 RotateY(float radian)
	{
		float sinTheta = sin(radian);
		float cosTheta = cos(radian);
		return RotateY(sinTheta, cosTheta);
	}

	static Matrix3x3 RotateY(float sinTheta, float cosTheta)
	{
		return Matrix3x3
		(
			Vector3f(cosTheta, 0.0f, -sinTheta),
			Vector3f(0.0f, 1.0f, 0.0f),
			Vector3f(sinTheta, 0.0f, cosTheta)
		);
	}

	static Matrix3x3 RotateZ(float radian)
	{
		float sinTheta = sin(radian);
		float cosTheta = cos(radian);
		return RotateZ(sinTheta, cosTheta);
	}

	static Matrix3x3 RotateZ(float sinTheta, float cosTheta)
	{
		return Matrix3x3
		(
			Vector3f(cosTheta, -sinTheta, 0.0f),
			Vector3f(sinTheta, cosTheta, 0.0f),
			Vector3f(0.0f, 0.0f, 1.0f)
		);
	}

	static Matrix3x3 Rotate(float radianX, float radianY, float radianZ)
	{
		Matrix3x3 mx = RotateX(radianX);
		Matrix3x3 my = RotateY(radianY);
		Matrix3x3 mz = RotateZ(radianZ);
		return mz * my * mx;
	}

	static Matrix3x3 FromTo(const Vector3f& from, const Vector3f& to)
	{
		const float kEpsilon = 0.00001f;

		Vector3f vec1 = Vector3f::Normalize(from);
		Vector3f vec2 = Vector3f::Normalize(to);
		float cosTheta = Vector3f::Dot(vec1, vec2);

		// When "from" almost equals to "to"
		if (cosTheta > 1.0f - kEpsilon)
		{
			return Matrix3x3::Identity;
		}

		// When "from" almost equals to negative "to"
		if (cosTheta < -1.0f + kEpsilon)
		{
			Vector3f vecRef = Vector3f::Right;
			if (Vector3f::Dot(vec1, vecRef) > 1.0f - kEpsilon)
				vecRef = Vector3f::Forward;

			Vector3f vecUp = Vector3f::Normalize(Vector3f::Cross(vec1, vecRef));
			Vector3f vecRight = Vector3f::Normalize(Vector3f::Cross(vecUp, vec1));
			Vector3f vecForward = vec1;
			Matrix3x3 matrixCoordinateFrom = Matrix3x3(vecRight, vecUp, vecForward);
			Matrix3x3 matrixCoordinateTo = Matrix3x3(-vecRight, vecUp, -vecForward);
			Matrix3x3 matrixCoordinateTransform = Matrix3x3::Transpose(matrixCoordinateFrom) * matrixCoordinateTo;
			return matrixCoordinateTransform;
		}

		// When "from" not parallax to "to"
		Vector3f v = Vector3f::Cross(vec1, vec2);
		float c = Vector3f::Dot(vec1, vec2);
		float k = 1.0f / (c + 1.0f);
		return Matrix3x3
		(
			Vector3f(v.x * v.x * k + c, v.x * v.y * k + v.z, v.x * v.z * k - v.y),
			Vector3f(v.y * v.x * k - v.z, v.y * v.y * k + c, v.y * v.z * k + v.x),
			Vector3f(v.z * v.x * k + v.y, v.z * v.y * k - v.x, v.z * v.z * k + c)
		);
	}

	static Vector3f TransformVector(const Matrix3x3& m, const Vector3f& vec)
	{
		Vector3f r0 = Vector3f(m.c0.x, m.c1.x, m.c2.x);
		Vector3f r1 = Vector3f(m.c0.y, m.c1.y, m.c2.y);
		Vector3f r2 = Vector3f(m.c0.z, m.c1.z, m.c2.z);
		return Vector3f(Vector3f::Dot(r0, vec), Vector3f::Dot(r1, vec), Vector3f::Dot(r2, vec));
	}

	static Matrix3x3 Transpose(const Matrix3x3& matrix)
	{
		return Matrix3x3
		(
			Vector3f(matrix.c0.x, matrix.c1.x, matrix.c2.x),
			Vector3f(matrix.c0.y, matrix.c1.y, matrix.c2.y),
			Vector3f(matrix.c0.z, matrix.c1.z, matrix.c2.z)
		);
	}

public:

	static const Matrix3x3 Identity;

public:

	Vector3f c0;
	Vector3f c1;
	Vector3f c2;
};

const Matrix3x3 Matrix3x3::Identity = Matrix3x3(Vector3f::Right, Vector3f::Up, Vector3f::Forward);