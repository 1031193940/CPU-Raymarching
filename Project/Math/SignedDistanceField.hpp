#pragma once

////////////////////////////////////////////////////////////
// Incldues ////////////////////////////////////////////////
////////////////////////////////////////////////////////////

#include "Vector3f.hpp"
#include "Quaternion.hpp"
#include "MathUtility.hpp"

////////////////////////////////////////////////////////////
// Classes /////////////////////////////////////////////////
////////////////////////////////////////////////////////////

class SignedDistanceField
{
private:

	SignedDistanceField() {}
	~SignedDistanceField() {}

public:

	inline static float SDFUnion(float sdf1, float sdf2)
	{
		return MathUtility::Min(sdf1, sdf2);
	}

	inline static float SDFSubtract(float sdf1, float sdf2)
	{
		return MathUtility::Max(sdf1, -sdf2);
	}

	inline static float SDFIntersect(float sdf1, float sdf2)
	{
		return MathUtility::Max(sdf1, sdf2);
	}

	inline static float SDFPlane(const Vector3f& positionWS, const Vector3f& planePoint, const Vector3f& planeNormal)
	{
		Quaternion quatWorldToLocal(planeNormal, Vector3f::Up);
		Vector3f localPosition = Quaternion::RotateVector(quatWorldToLocal, positionWS - planePoint);
		return localPosition.y;
	}

	inline static float SDFSphere(const Vector3f& positionWS, const Vector3f& sphereCenterWS, float radius)
	{
		Vector3f transformedPositionWS = positionWS - sphereCenterWS;
		float distanceToSphereSurface = Vector3f::Length(transformedPositionWS) - radius;
		return distanceToSphereSurface;
	}

	inline static float SDFBox(const Vector3f& positionWS, const Vector3f& boxCenterWS, const Vector3f& boxSize)
	{
		Vector3f transformedPositionWS = positionWS - boxCenterWS;
		Vector3f q = Vector3f::Abs(transformedPositionWS) - boxSize;
		return Vector3f::Length(Vector3f::Max(q, Vector3f::Zero)) + MathUtility::Min(MathUtility::Max(q.x, q.y, q.z), 0.0f);
	}

};