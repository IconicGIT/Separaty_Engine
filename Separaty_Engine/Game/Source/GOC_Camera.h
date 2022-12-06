#ifndef __Camera_H__
#define __Camera_H__


#include "GameObject.h"
#include "Globals.h"
#include <vector>


#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glmath.h"

#include "MathGeoLib/MathGeoLib.h"

class GameObject;
class GameObjectComponent;

class GOC_Camera : public GameObjectComponent
{
public:
	GOC_Camera(GameObject* gameObjectAttached)
	{
		GOC_type = GOC_Type::GOC_CAMERA;
		gameObject = gameObjectAttached;

		frustum.type = PerspectiveFrustum;

		if (gameObject != nullptr && gameObject->transform != nullptr)
		{
			/*frustum.pos = gameObject->transform->GetPosition();*/
			/*frustum.front = gameObject->transform->GetRotation() * float3::unitZ;
			frustum.up = gameObject->transform->GetRotation() * float3::unitY;*/
		}
		else
		{
			frustum.pos = float3::zero;
			frustum.front = float3::unitZ;
			frustum.up = float3::unitY;
		}

		frustum.nearPlaneDistance = 1.0f;
		frustum.farPlaneDistance = 1000.0f;
		frustum.verticalFov = 60.0f * DEGTORAD;
		frustum.horizontalFov = 2.f * atan(tan(frustum.verticalFov * 0.5f) * (SCREEN_WIDTH / SCREEN_HEIGHT));

		frustum.pos = position;
	}

	void UpdateFrust(GameObject* gameObject);


	bool Execute()
	{
		return true;
	}

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

	~GOC_Camera() {}


	void		SetPos(float x, float y, float z);
	void		SetPos(float3 pos);
	float3		GetPos();



public:
	Frustum frustum;

	float nearPlaneDistance = 0.0f;
	float farPlaneDistance = 0.0f;
	float verticalFov = 0.0f;
	float horizontalFov = 0.0f;

	float3 position = float3::zero;
};

#endif // !__Camera_H__
#pragma once
