#pragma once

#include "SDFObject.hpp"

class SDFSphere : public SDFObject
{
public:

	SDFSphere() : SDFObject(Vector3f::Zero, Quaternion::Identity), m_Radius(0.0f)
	{
		// DO NOTHING
	}

	SDFSphere(const Vector3f& position, float radius) : SDFObject(position, Quaternion::Identity), m_Radius(radius)
	{
		// DO NOTHING
	}

	SDFSphere(const Vector3f& position, const Quaternion& quaternion, float radius) : SDFObject(position, quaternion), m_Radius(radius)
	{
		// DO NOTHING
	}

public:

	virtual float Distance(const Vector3f& position)
	{
		Vector3f transformedSpherePosition = position - m_Position;
		return Vector3f::Length(transformedSpherePosition) - m_Radius;
	}

public:

	float m_Radius;

};