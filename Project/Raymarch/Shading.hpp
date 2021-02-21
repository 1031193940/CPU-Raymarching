#pragma once

#include "../Math/Vector2f.hpp"
#include "../Math/Vector3f.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/MathUtility.hpp"

#include "../Scene/Ray.hpp"
#include "../Scene/Light.hpp"
#include "../Scene/Camera.hpp"
#include "../Scene/Scene.hpp"
#include "../Scene/SDFBox.hpp"
#include "../Scene/SDFPlane.hpp"
#include "../Scene/SDFSphere.hpp"
#include "../Scene/SDFUnion.hpp"
#include "../Scene/SDFSubtract.hpp"
#include "../Scene/SDFIntersect.hpp"

#include "../Image/Color3f.hpp"
#include "../Image/Texture2D.hpp"

#include "Raymarch.hpp"

class RaymarchShading
{
public:

	RaymarchShading()
	{
		// TODO
	}

public:

	void Initialize(Texture2D& backbuffer)
	{
		// Camera
		_camera.m_Position = kCameraPosition;
		_camera.m_Rotation = Quaternion::FromTo(Vector3f::Forward, Vector3f::Normalize(-kCameraPosition));

		// Light
		_light.m_Color = kLightColor;
		_light.m_Position = kLightPosition;
		_light.m_Direction = Vector3f::Normalize(kLightPosition);

		// Plane
		_plane.m_Position = kPlanePosition;
		_plane.m_Normal = kPlaneNormal;
		_plane.m_Rotation = kPlaneRotation;

		// Box - Sphere
		_sphere.m_Radius = kSphereRadius;
		_sphere.m_Position = kSpherePosition;
		_sphere.m_Rotation = kSphereRotation;
		_box.m_Position = kBoxPosition;
		_box.m_Size = kBoxSize;
		_box.m_Rotation = kBoxRotation;
		_boxSubtractSphere.m_ObjectA = &_box;
		_boxSubtractSphere.m_ObjectB = &_sphere;
		_boxSubtractSphere.m_Rotation = kBoxSphereRotation;

		// Scene
		_scene.AddObject(&_plane);
		_scene.AddObject(&_boxSubtractSphere);
	}

	void Release(void)
	{
	}

	void Draw(Texture2D& backbuffer)
	{
		int iWindowWidth = backbuffer.GetWidth();
		int iWindowHeight = backbuffer.GetHeight();
		float fWindowWidth = (float)iWindowWidth;
		float fWindowHeight = (float)iWindowHeight;
		float fWindowRatio = fWindowWidth / fWindowHeight;

		Vector2f uv = Vector2f::Zero;
		for (int y = 0; y < iWindowHeight; ++y)
		{
			for (int x = 0; x < iWindowWidth; ++x)
			{
				uv.x = (float)x / fWindowWidth;
				uv.y = (float)y / fWindowHeight;
				backbuffer.Pixel(x, y) = FragmentFunc(uv, fWindowRatio);
			}
		}
	}

private:

	Color3f FragmentFunc(const Vector2f& uv, float ratio)
	{
		Vector2f ratioUV = (uv * 2.0f - 1.0f) * Vector2f(ratio, 1.0f);
		
		// Create ray
		Ray ray;
		ray.m_Origin = _camera.m_Position;
		ray.m_Direction = Vector3f::Normalize(Quaternion::RotateVector(_camera.m_Rotation, Vector3f(ratioUV.x, ratioUV.y, 1.0f)));

		// Raymarching for hit point
		float raymarchingDistance = Raymarching(ray);

		// Final color shading
		Color3f surfaceColor = Color3f::Black;
		if (raymarchingDistance < kRaymarchDistanceMax)
		{
			Vector3f surfacePosition = ray.m_Origin + ray.m_Direction * raymarchingDistance;
			Vector3f surfaceNormal = GetSurfaceNormal(surfacePosition);
			surfaceColor = Lighting(surfacePosition, surfaceNormal);
		}

		return surfaceColor;
	}

	float Raymarching(const Ray& ray)
	{
		float raymarchingDistance = 0.0f;
		for (int i = 0; i < kRaymarchStepMax; ++i)
		{
			Vector3f raymarchingPosition = ray.m_Origin + ray.m_Direction * raymarchingDistance;
			float distanceToNearestSurface = _scene.GetMinDistance(raymarchingPosition);
			if (distanceToNearestSurface < kRaymarchDistanceMin)
				break;

			raymarchingDistance += distanceToNearestSurface;
			if (raymarchingDistance > kRaymarchDistanceMax)
				break;
		}

		return raymarchingDistance;
	}

	float Shadowing(const Vector3f& position)
	{
		// Shadow Ray
		Ray rayShadow;
		rayShadow.m_Origin = position;
		rayShadow.m_Direction = _light.m_Direction;

		// Ray marching for shadow
		float shadowDistanceToNearestSurface = Raymarching(rayShadow);
		if (shadowDistanceToNearestSurface < kRaymarchDistanceMax)
			return 0.0f;

		return 1.0f;
	}

	Vector3f GetSurfaceNormal(const Vector3f& surfacePosition)
	{
		float distanceToNearestSurface = _scene.GetMinDistance(surfacePosition);
		Vector3f normalDirection = Vector3f
		(
			distanceToNearestSurface - _scene.GetMinDistance(surfacePosition - Vector3f(0.01f, 0.00f, 0.00f)),
			distanceToNearestSurface - _scene.GetMinDistance(surfacePosition - Vector3f(0.00f, 0.01f, 0.00f)),
			distanceToNearestSurface - _scene.GetMinDistance(surfacePosition - Vector3f(0.00f, 0.00f, 0.01f))
		);

		return Vector3f::Normalize(normalDirection);
	}

	Color3f Lighting(const Vector3f& position, const Vector3f& normalDirection)
	{
		// Lambert
		float NdotL = Vector3f::Dot(_light.m_Direction, normalDirection);
		float lambert = MathUtility::Saturate(NdotL);

		// Shadow
		float shadow = Shadowing(position + normalDirection * kRaymarchDistanceMin * 2.0f);

		// Output
		float lightingIntensity = MathUtility::Lerp(kLightGI, 1.0f, lambert * shadow);
		Color3f outputColor = kRaymarchSurfaceColor * _light.m_Color * lightingIntensity;
		return outputColor;
	}

private:

	Scene _scene;
	Light _light;
	Camera _camera;

	SDFBox _box;
	SDFSphere _sphere;
	SDFSubtract _boxSubtractSphere;

	SDFPlane _plane;

private:

	const float    kLightGI = 0.3f;
	const Color3f  kLightColor = Color3f::White;
	const Vector3f kLightPosition = Vector3f(20.0f, 20.0f, -5.0f);

	const Vector3f kCameraPosition = Vector3f(0.0f, 1.5f, -4.0f);

	const float      kSphereRadius = 1.0f;
	const Vector3f   kSpherePosition = Vector3f(0.0f, 0.0f, 0.0f);
	const Quaternion kSphereRotation = Quaternion::Identity;
	const Vector3f   kBoxPosition = Vector3f(0.0f, 0.0f, 0.0f);
	const Vector3f   kBoxSize = Vector3f(0.8f, 0.8f, 0.8f);
	const Quaternion kBoxRotation = Quaternion::Identity;
	const Quaternion kBoxSphereRotation = Quaternion::AxisRadian(Vector3f::Up, MathUtility::PI * 0.15f);

	const Vector3f   kPlanePosition = Vector3f(0.0f, -0.8f, 0.0f);
	const Vector3f   kPlaneNormal = Vector3f(0.0f, 1.0f, 0.0f);
	const Quaternion kPlaneRotation = Quaternion::Identity;

	const int     kRaymarchStepMax = 100;
	const float   kRaymarchDistanceMax = 100.0f;
	const float   kRaymarchDistanceMin = 0.0001f;
	const Color3f kRaymarchSurfaceColor = Color3f(0.5f, 0.8f, 1.0f);
};