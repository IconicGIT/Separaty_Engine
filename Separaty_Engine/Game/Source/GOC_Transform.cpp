#include "GOC_Transform.h"



GOC_Transform::GOC_Transform(GameObject* gameObjectAttached)
{
	transform = IdentityMatrix;
	GOC_type = GOC_Type::GOC_TRANSFORM;

}

GOC_Transform::~GOC_Transform()
{
}

void GOC_Transform::SetPos(float x, float y, float z)
{
	transform.translate(x, y, z);
}


// ------------------------------------------------------------
void GOC_Transform::SetRotation(float angle, const vec3& u)
{
	transform.rotate(angle, u);
}

// ------------------------------------------------------------
void GOC_Transform::Scale(float x, float y, float z)
{
	transform.scale(x, y, z);
}

bool GOC_Transform::Execute()
{	

	return true;
}