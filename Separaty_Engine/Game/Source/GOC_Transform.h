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
		return transform.translation();
	}

	vec3 GetScale() const
	{
		return transform.scaling();
	}

	//vec3 GetScale() const
	//{
	//	return transform.scaling();
	//}

	bool Execute();

	mat4x4 Get4x4Matrix() const
	{
		return transform;
	}

	void Set4x4Matrix(mat4x4 matrix) 
	{
		transform = matrix;
	}
	mat4x4 Get4x4MatrixLocal() const
	{
		return transform;
	}

	void Set4x4MatrixLocal(mat4x4 matrix)
	{
		transformLocal = matrix;
	}

	void ApplyTransformations()
	{
		transform = translation * transformLocal * rotation;
	}

	mat4x4 translation = IdentityMatrix;
	mat4x4 rotation = IdentityMatrix;
	mat4x4 transform = IdentityMatrix;
	mat4x4 transformLocal = IdentityMatrix;
private:


	
	
};

