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

	bool noColors = true;

private:
	std::string name;

	Frustum frustum;

	float3 position;
	Quat rotation;

	bool editingModeWorld = true;
};
