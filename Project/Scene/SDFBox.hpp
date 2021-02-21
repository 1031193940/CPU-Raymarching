#pragma once

#include "SDFObject.hpp"

class SDFBox : public SDFObject
{
public:

	SDFBox() : SDFObject(Vector3f::Zero, Quaternion::Identity), m_Size(Vector3f::Zero)
	{
		// DO NOTHING
	}

	SDFBox(const Vector3f& position, const Vector3f& size) : SDFObject(position, Quaternion::Identity), m_Size(size)
	{
		// DO NOTHING
	}

	SDFBox(const Vector3f& position, const Quaternion& quaternion, const Vector3f& size) : SDFObject(position, quaternion), m_Size(size)
	{
		// DO NOTHING
	}

public:

	virtual float Distance(const Vector3f& position)
	{
		Vector3f transformedPosition = Quaternion::RotateVector(Quaternion::Conjugate(m_Rotation), position - m_Position);
		Vector3f q = Vector3f::Abs(transformedPosition) - m_Size;
		return Vector3f::Length(Vector3f::Max(q, Vector3f::Zero)) + MathUtility::Min(MathUtility::Max(q.x, q.y, q.z), 0.0f);
	}

public:

	Vector3f m_Size;

};