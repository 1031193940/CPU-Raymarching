#pragma once

#include "SDFObject.hpp"

class SDFUnion : public SDFObject
{
public:

	SDFUnion() : SDFObject(Vector3f::Zero, Quaternion::Identity)
	{
		// DO NOTHING
	}

	SDFUnion(const Vector3f& position, const Quaternion& quaternion) : SDFObject(position, quaternion)
	{
		// DO NOTHING
	}

public:

	virtual float Distance(const Vector3f& position)
	{
		Vector3f transformedPosition = Quaternion::RotateVector(m_Rotation, position - m_Position);
		float distanceToObjectA = m_ObjectA->Distance(transformedPosition);
		float distanceToObjectB = m_ObjectB->Distance(transformedPosition);
		return fminf(distanceToObjectA, distanceToObjectB);
	}

public:

	SDFObject* m_ObjectA = nullptr;
	SDFObject* m_ObjectB = nullptr;
};