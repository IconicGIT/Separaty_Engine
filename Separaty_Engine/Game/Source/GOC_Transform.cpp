#include "GOC_Transform.h"



GOC_Transform::GOC_Transform(GameObject* gameObjectAttached, int id)
{
	this->id = id;
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

void GOC_Transform::ApplyTransformations()
{

	translationWorld = translationLocal;
	rotationWorld = rotationLocal;
	scalingWorld = scalingLocal;
	if (gameObject->parent != nullptr)
	{
		//12 13 14
		translationWorld = AddMatrices(gameObject->parent->transform->translationWorld, translationLocal);
		translationWorld.M[0] = translationWorld.M[5] = translationWorld.M[10] = translationWorld.M[15] = 1;
		rotationWorld = gameObject->parent->transform->rotationWorld * rotationLocal;
		scalingWorld = gameObject->parent->transform->scalingWorld * scalingLocal;
	}

	ApplyTransformationsWorld();
}

void GOC_Transform::ApplyTransformationsWorld()
{
	transformWorld =  translationWorld * rotationWorld * scalingWorld;


	for (GameObject* go : gameObject->GetChildren())
	{
		go->transform->ApplyTransformations();
	}

}



bool GOC_Transform::SaveState(JSON_Value* file, std::string root) const
{
	json_object_dotset_number(json_object(file), std::string(root + "transform.position.x").c_str(), (double)gameObject->transform->translationLocal.translation().x);
	json_object_dotset_number(json_object(file), std::string(root + "transform.position.y").c_str(), (double)gameObject->transform->translationLocal.translation().y);
	json_object_dotset_number(json_object(file), std::string(root + "transform.position.z").c_str(), (double)gameObject->transform->translationLocal.translation().z);

	json_object_dotset_number(json_object(file), std::string(root + "transform.rotationRad.x").c_str(), (double)gameObject->transform->rotationEulerLocal.x);
	json_object_dotset_number(json_object(file), std::string(root + "transform.rotationRad.y").c_str(), (double)gameObject->transform->rotationEulerLocal.y);
	json_object_dotset_number(json_object(file), std::string(root + "transform.rotationRad.z").c_str(), (double)gameObject->transform->rotationEulerLocal.z);

	json_object_dotset_number(json_object(file), std::string(root + "transform.scale.x").c_str(), (double)gameObject->transform->scalingLocal.scaling().x);
	json_object_dotset_number(json_object(file), std::string(root + "transform.scale.y").c_str(), (double)gameObject->transform->scalingLocal.scaling().y);
	json_object_dotset_number(json_object(file), std::string(root + "transform.scale.z").c_str(), (double)gameObject->transform->scalingLocal.scaling().z);

	return true;
}

bool GOC_Transform::LoadState(JSON_Value* file, std::string root)
{

	//load position
	mat4x4 translation = IdentityMatrix;

	vec3 newPos = vec3(
		json_object_dotget_number(json_object(file), std::string(root + "transform.position.x").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + "transform.position.y").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + "transform.position.z").c_str())
		);


	translation.translate(newPos.x, newPos.y, newPos.z);

	translationLocal = translation;

	//Load rotation

	vec3 rotRad = vec3(
		json_object_dotget_number(json_object(file), std::string(root + "transform.rotationRad.x").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + "transform.rotationRad.y").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + "transform.rotationRad.z").c_str())
	);
	
	Quat rotatorQuat = Quat::FromEulerXYZ(rotRad.x, rotRad.y, rotRad.z);
	aiQuaternion rotationQuat(rotatorQuat.w, rotatorQuat.x, rotatorQuat.y, rotatorQuat.z);


	aiMatrix3x3* tempMat3 = new aiMatrix3x3;

	aiQuaternion* tempRotationQuat = new aiQuaternion(rotationQuat);

	//aiMatrix4FromScalingQuaternionPosition(tempMat, tempScale, tempRotationQuat, tempPosition);
	aiMatrix3FromQuaternion(tempMat3, tempRotationQuat);

	mat4x4 resMat = IdentityMatrix;

	resMat[0] = (float)tempMat3->a1;
	resMat[1] = (float)tempMat3->a2;
	resMat[2] = (float)tempMat3->a3;
	resMat[3] = 0;

	resMat[4] = (float)tempMat3->b1;
	resMat[5] = (float)tempMat3->b2;
	resMat[6] = (float)tempMat3->b3;
	resMat[7] = 0;

	resMat[8] = (float)tempMat3->c1;
	resMat[9] = (float)tempMat3->c2;
	resMat[10] = (float)tempMat3->c3;
	resMat[11] = 0;

	resMat[12] = 0;
	resMat[13] = 0;
	resMat[14] = 0;
	resMat[15] = 1;

	resMat.transpose();

	rotationLocal = resMat;
	rotationEulerLocal = float3(rotRad.x, rotRad.y, rotRad.z);


	//load scaling
	mat4x4 scaling = IdentityMatrix;

	vec3 newScale = vec3(
		json_object_dotget_number(json_object(file), std::string(root + "transform.scale.x").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + "transform.scale.y").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + "transform.scale.z").c_str())
	);

	scaling.scale(newScale.x, newScale.y, newScale.z);

	scalingLocal = scaling;

	ApplyTransformations();

	return true;
}
