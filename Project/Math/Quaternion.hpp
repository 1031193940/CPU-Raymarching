#pragma once

////////////////////////////////////////////////////////////
// Includes ////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include "Vector3f.hpp"
#include "Matrix3x3.hpp"
#include "MathUtility.hpp"

////////////////////////////////////////////////////////////
// Classes /////////////////////////////////////////////////
////////////////////////////////////////////////////////////

class Quaternion
{
public:

	Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		// DO NOTHING
	}

	Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{
		// DO NOTHING
	}

	Quaternion(const Vector3f& axis, float radian)
	{
		float theta = radian * 0.5f;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		x = axis.x * sinTheta;
		y = axis.y * sinTheta;
		z = axis.z * sinTheta;
		w = cosTheta;
	}

	Quaternion(const Vector3f& from, const Vector3f& to)
	{
		(*this) = FromTo(from, to);
	}

	~Quaternion()
	{
		// DO NOTHING
	}

public:

	inline Quaternion& operator=(const Quaternion& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }

	inline Quaternion operator*(const Quaternion& other) const { return Quaternion::Multiply(*this, other); }

	inline bool operator==(const Quaternion& other) const { return (x == other.x && y == other.y && z == other.z && w == other.w); }
	inline bool operator!=(const Quaternion& other) const { return (x != other.x || y != other.y || z != other.z || w != other.w); }

public:

	static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion
		(
			(q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y),
			(q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x),
			(q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w),
			(q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z)
		);
	}

	static Quaternion FromTo(const Vector3f& from, const Vector3f& to)
	{
		Matrix3x3 matrixFromTo = Matrix3x3::FromTo(from, to);
		return MatrixToQuaternion(matrixFromTo);
	}

	static Quaternion AxisRadian(const Vector3f& axis, float radian)
	{
		return Quaternion(axis, radian);
	}

	static Quaternion Conjugate(const Quaternion& q)
	{
		return Quaternion(-q.x, -q.y, -q.z, q.w);
	}

	static Quaternion MatrixToQuaternion(Matrix3x3& m)
	{
		float w = sqrt(1.0f + m(0, 0) + m(1, 1) + m(2, 2)) * 0.5f;
		float scaler = 1.0f / (w * 4.0f);
		float x = (m(2, 1) - m(1, 2)) * scaler;
		float y = (m(0, 2) - m(2, 0)) * scaler;
		float z = (m(1, 0) - m(0, 1)) * scaler;
		return Quaternion(x, y, z, w);
	}

	static Vector3f RotateVector(const Quaternion& quat, const Vector3f& pos)
	{
		Quaternion quatPos = Quaternion(pos.x, pos.y, pos.z, 0.0f);
		Quaternion quatRotated = quat * quatPos * Quaternion::Conjugate(quat);
		return Vector3f(quatRotated.x, quatRotated.y, quatRotated.z);
	}

public:

	float x, y, z, w;

public:

	static const Quaternion Identity;

};

const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 1.0f, 0.0f);