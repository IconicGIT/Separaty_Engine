#pragma once

#include "Module.h"
#include "Globals.h"

class Editor;
struct EngineConfig;

class Inspector : public Module
{
public:
	Inspector();
	~Inspector();

	update_status Update(float dt)override;

	GameObject* selectedGameObject = nullptr;
	GameObject* destinationGameObject = nullptr;
	std::vector<GameObject*> selectedGameObjects;

	float4x4 transformMatrix;
	float4x4 transformMatrixLocal;
private:
	std::string name;

	Frustum frustum;

	float3 position;
	Quat rotation;

	bool editingModeWorld = true;
};