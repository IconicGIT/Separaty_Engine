#pragma once

#include "GameObject.h"
#include <vector>
#include "glmath.h"


class GameObjectComponent;

class GOC_Transform : public GameObjectComponent
{
public:
	GOC_Transform(GameObject* gameObjectAttached, int id);
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

	void ApplyTransformationsWorld();

	void ApplyTransformations();
	


	void ResetMatrices()
	{
		translationLocal = IdentityMatrix;
		rotationLocal = IdentityMatrix;
		rotationEulerLocal = float3(0, 0, 0);
		scalingLocal = IdentityMatrix;
		ApplyTransformations();
	}

	void ResetTranslation()
	{
		translationLocal = IdentityMatrix;
		ApplyTransformations();
	}

	void ResetRotation()
	{
		rotationLocal = IdentityMatrix;
		rotationEulerLocal = float3(0, 0, 0);
		ApplyTransformations();
	}

	void ResetScale()
	{
		scalingLocal = IdentityMatrix;
		ApplyTransformations();
	}

	mat4x4 AddMatrices(const mat4x4& Matrix1, const mat4x4& Matrix2)
	{
		mat4x4 Matrix3;

		Matrix3.M[0] = Matrix1.M[0] + Matrix2.M[0];
		Matrix3.M[1] = Matrix1.M[1] + Matrix2.M[1];
		Matrix3.M[2] = Matrix1.M[2] + Matrix2.M[2];
		Matrix3.M[3] = Matrix1.M[3] + Matrix2.M[3];
		Matrix3.M[4] = Matrix1.M[4] + Matrix2.M[4];
		Matrix3.M[5] = Matrix1.M[5] + Matrix2.M[5];
		Matrix3.M[6] = Matrix1.M[6] + Matrix2.M[6];
		Matrix3.M[7] = Matrix1.M[7] + Matrix2.M[7];
		Matrix3.M[8] = Matrix1.M[8] + Matrix2.M[8];
		Matrix3.M[9] = Matrix1.M[9] + Matrix2.M[9];
		Matrix3.M[10] = Matrix1.M[10] + Matrix2.M[10];
		Matrix3.M[11] = Matrix1.M[11] + Matrix2.M[11];
		Matrix3.M[12] = Matrix1.M[12] + Matrix2.M[12];
		Matrix3.M[13] = Matrix1.M[13] + Matrix2.M[13];
		Matrix3.M[14] = Matrix1.M[14] + Matrix2.M[14];
		Matrix3.M[15] = Matrix1.M[15] + Matrix2.M[15];

		return Matrix3;
	}

	mat4x4 translationWorld = IdentityMatrix;
	mat4x4 rotationWorld = IdentityMatrix;
	Quat rotationQuatWorld = Quat({ 0,0,0,1 });
	float3 rotationEulerWorld = float3(0, 0, 0);
	mat4x4 scalingWorld = IdentityMatrix;
	mat4x4 transformWorld = IdentityMatrix;

	mat4x4 translationLocal = IdentityMatrix;
	Quat rotationQuatLocal = Quat({ 0,0,0,1 });
	float3 rotationEulerLocal= float3(0, 0, 0);
	mat4x4 rotationLocal = IdentityMatrix;
	mat4x4 scalingLocal = IdentityMatrix;
	mat4x4 transformLocal = IdentityMatrix;

	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

private:


	
	
};

