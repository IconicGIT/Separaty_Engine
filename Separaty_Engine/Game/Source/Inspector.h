#pragma once

#include "Module.h"
#include "Globals.h"
#include "UIFunctions.h"

class Editor;
class UIFunctions;
struct EngineConfig;



class Inspector : public Module
{
public:
	Inspector();
	~Inspector();

	update_status Update(float dt)override;

	GameObject* selectedGameObject = nullptr;
	GameObject* destinationGameObject = nullptr;

	float4x4 transformMatrix;
	float4x4 transformMatrixLocal;

	UIFunctions* UImanager;


	bool useCamInPlay;

	//Colors
	bool noColors = true;

	//Shape
	bool boxShape = true;
	bool sphereShape;
	bool coneShape;

	//Box Emision
	bool randomBEmision;
	bool CenterBEmision;
	bool BorderBEmision;

	//Sphere Emision
	bool randomSEmision;
	bool CenterSEmision;
	bool BorderSEmision;

	//Cone Emision
	bool randomCEmision;
	bool CenterCEmision;
	bool BorderCEmision;

	bool activeBox = false;

	AABB boxCreation = AABB(float3(-0.5f, -0.5f, -0.5f), float3(0.5f, 0.5f, 0.5f));
	Sphere sphereCreation = Sphere(float3::zero, 1.0f);
	Circle circleCreation = Circle(float3::unitY, float3::unitY, 1.0f);

	//float3 RandPos();

	math::LCG randomMath;
private:
	std::string name;

	Frustum frustum;

	float3 position;
	Quat rotation;

	bool editingModeWorld = true;
};
