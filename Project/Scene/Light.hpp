#pragma once

#include "../Math/Vector3f.hpp"
#include "../Image/Color3f.hpp"

struct Light
{
	Color3f  m_Color;
	Vector3f m_Position;
	Vector3f m_Direction;
};