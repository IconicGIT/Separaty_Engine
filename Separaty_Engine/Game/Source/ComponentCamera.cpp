#include "Application.h"

#include "ComponentCamera.h"
#include "GameObject.h"

#include "Geometry/Frustum.h"

void GOC_Camera::UpdateFrust(GameObject* gameObject)
{
	if (gameObject != nullptr && gameObject->transform != nullptr)
	{
		/*frustum.pos = gameObject->transform->GetPosition();
		frustum.front = gameObject->transform->GetRotation() * float3::unitZ;
		frustum.up = gameObject->transform->GetRotation() * float3::unitY;*/
	}
	else
	{
		frustum.pos = float3::zero;
		frustum.front = float3::unitZ;
		frustum.up = float3::unitY;
	}
}

float4x4 GOC_Camera::GetViewMatrix()
{
	float4x4 matrix;

	matrix = frustum.ViewMatrix();
	matrix.Transpose();

	return matrix;
}

float4x4 GOC_Camera::GetProjectionMatrix()
{
	float4x4 matrix;

	matrix = frustum.ProjectionMatrix();
	matrix.Transpose();

	return matrix;
}

void GOC_Camera::SetPos(float x, float y, float z)
{
	frustum.pos = float3(x, y, z);
}
void GOC_Camera::SetPos(float3 pos)
{
	frustum.pos = pos;
}

float3 GOC_Camera::GetPos()
{
	return frustum.pos;
}