#pragma once

#include "../Math/Vector3f.hpp"
#include "../Math/Matrix3x3.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/MathUtility.hpp"

class SDFObject
{
public:

	SDFObject() : m_Position(Vector3f::Zero), m_Rotation(Quaternion::Identity)
	{
		// DO NOTHING
	}

	SDFObject(const Vector3f& position, const Quaternion& quaternion) : m_Position(position), m_Rotation(quaternion)
	{
		// DO NOTHING
	}

public:

	virtual float Distance(const Vector3f& position) = 0;

public:

	Vector3f m_Position;
	Quaternion m_Rotation;

};