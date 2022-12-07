#ifndef __Camera_H__
#define __Camera_H__


#include "GameObject.h"
#include "Globals.h"
#include <vector>
#include "GameObjComponent.h";


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
	GOC_Camera(GameObject* gameObjectAttached);

	void UpdateFrustum();
	void DrawCube(static float3* corners, Color color);


	bool Execute();


	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

	~GOC_Camera() {}


	void		SetPos(float x, float y, float z);
	void		SetPos(float3 pos);
	float3		GetPos();

	void LookAt(const vec3& Spot);

public:
	Frustum frustum;

	float nearPlaneDistance = 0.0f;
	float farPlaneDistance = 0.0f;
	float verticalFov = 0.0f;
	float horizontalFov = 0.0f;



	bool isCurrent = false;

	vec3 X, Y, Z, Position, Reference;
	vec bboxPoints[8];
	Color frustumColor;
private:


	/*LCG lcg;*/
	mat4x4 ViewMatrix, ViewMatrixInverse;

	void CalculateViewMatrix()
	{
		ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
		ViewMatrixInverse = inverse(ViewMatrix);
	}
};

#endif // !__Camera_H__
#pragma once
