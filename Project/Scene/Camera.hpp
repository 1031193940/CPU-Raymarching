#pragma once

#include "../Math/Vector3f.hpp"
#include "../Math/Quaternion.hpp"

class Camera
{
public:

	Camera() : m_Position(Vector3f::Zero), m_Rotation(Quaternion::Identity)
	{
		// TODO
	}

	Camera(const Vector3f& position) : m_Position(position), m_Rotation(Quaternion::Identity)
	{
		// TODO
	}

	Camera(const Vector3f& position, const Quaternion& rotation) : m_Position(position), m_Rotation(rotation)
	{
		// TODO
	}

public:

	Vector3f   m_Position;
	Quaternion m_Rotation;

};