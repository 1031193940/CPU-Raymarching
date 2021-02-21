#pragma once

#include "SDFObject.hpp"

class Scene
{
public:

	Scene() : _objectCount(0)
	{
		// DO NOTHING
	}

	~Scene()
	{
		// DO NOTHING
	}

public:

	inline void Clear()
	{
		_objectCount = 0;
	}

	inline void AddObject(SDFObject* object)
	{
		_objectList[_objectCount++] = object;
	}

	inline int GetObjectCount() const
	{
		return _objectCount;
	}

public:

	float GetMinDistance(const Vector3f& position) const
	{
		if (_objectCount == 0)
			return -1.0f;

		float distanceToNearestObject = _objectList[0]->Distance(position);
		for (int i = 1; i < _objectCount; ++i)
		{
			float distanceToObject = _objectList[i]->Distance(position);
			distanceToNearestObject = fminf(distanceToNearestObject, distanceToObject);
		}

		return distanceToNearestObject;
	}

private:

	int _objectCount;
	SDFObject* _objectList[32];

};