#pragma once

#include "GameObject.h"
#include <vector>
#include "glmath.h"


class GameObjectComponent;
class GameObject;

class GOC_Transform : public GameObjectComponent
{
public:
	GOC_Transform(GameObject* gameObjectAttached);
	~GOC_Transform();


	void SetPos(float x, float y, float z);
	void SetRotation(float angle, const vec3& u);
	void SetScale(float x, float y, float z);
	vec3 GetPosition() const
	{
		return transformWorld.translation();
	}

	vec3 GetScale() const
	{
		return transformWorld.scaling();
	}

	//vec3 GetScale() const
	//{
	//	return transform.scaling();
	//}

	bool Execute();

	mat4x4 Get4x4Matrix() const
	{
		return transformWorld;
	}

	void Set4x4Matrix(mat4x4 matrix) 
	{
		transformWorld = matrix;
	}
	mat4x4 Get4x4MatrixLocal() const
	{
		return transformWorld;
	}

	void Set4x4MatrixLocal(mat4x4 matrix)
	{
		transformLocal = matrix;
	}

	void ApplyTransformationsWorld()
	{
		transformWorld =  rotationWorld * translationWorld * scalingWorld;
		transformLocal = transformWorld * transformLocal;
	}

	void ApplyTransformationsLocal()
	{
		transformWorld = translationLocal * rotationLocal * scalingLocal;
		transformWorld = transformWorld * transformLocal;
	}

	mat4x4 translationWorld = IdentityMatrix;
	mat4x4 rotationWorld = IdentityMatrix;
	float3 rotationEulerWorld = float3(0, 0, 0);
	mat4x4 scalingWorld = IdentityMatrix;
	mat4x4 transformWorld = IdentityMatrix;

	mat4x4 translationLocal = IdentityMatrix;
	float3 rotationEulerLocal= float3(0, 0, 0);
	mat4x4 rotationLocal = IdentityMatrix;
	mat4x4 scalingLocal = IdentityMatrix;
	mat4x4 transformLocal = IdentityMatrix;



private:


	
	
};

