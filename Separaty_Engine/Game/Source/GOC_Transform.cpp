#include "GOC_Transform.h"



GOC_Transform::GOC_Transform(GameObject* gameObjectAttached)
{
	transformWorld = IdentityMatrix;
	transformLocal = IdentityMatrix;
	GOC_type = GOC_Type::GOC_TRANSFORM;
	gameObject = gameObjectAttached;
}

GOC_Transform::~GOC_Transform()
{
}

void GOC_Transform::SetPos(float x, float y, float z)
{
	transformWorld.translate(x, y, z);
}


// ------------------------------------------------------------
void GOC_Transform::SetRotation(float angle, const vec3& u)
{
	transformWorld.rotate(angle, u);
}

// ------------------------------------------------------------
void GOC_Transform::SetScale(float x, float y, float z)
{
	transformWorld.scale(x, y, z);
}

bool GOC_Transform::Execute()
{	

	return true;
}