#pragma once

#include "SDFObject.hpp"

class SDFPlane: public SDFObject
{
public:

	SDFPlane() : SDFObject(Vector3f::Zero, Quaternion::Identity), m_Normal(Vector3f::Up)
	{
		// DO NOTHING
	}

	SDFPlane(const Vector3f& position, const Vector3f& normal) : SDFObject(position, Quaternion::Identity), m_Normal(normal)
	{
		// DO NOTHING
	}

	SDFPlane(const Vector3f& position, const Quaternion& quaternion, const Vector3f& normal) : SDFObject(position, quaternion), m_Normal(normal)
	{
		// DO NOTHING
	}

public:

	virtual float Distance(const Vector3f& position)
	{
		return (position - m_Position).y;
		Quaternion quatWorldToLocal(m_Normal, Vector3f::Up);
		Vector3f transformedPosition = Quaternion::RotateVector(Quaternion::Conjugate(m_Rotation), position - m_Position);
		Vector3f localPosition = Quaternion::RotateVector(quatWorldToLocal, transformedPosition);
		return localPosition.y;
	}

public:

	Vector3f m_Normal;

};