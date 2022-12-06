#pragma once

#include "ModuleUI.h"
#include "Globals.h"
#include "GameObject.h"
#include "MathGeoLib/Math/Quat.h"
#include "ProjectPreferences.h"
class EngineSystem;
class GameObject;

//class ModuleUI;
class Module;

class UIFunctions : public Module
{
public:

	UIFunctions();

	~UIFunctions();

	bool Start();
	update_status Update(float dt) override;

	Preferences* showPreferences;

	//Hierarchy
	void DisplayTree(GameObject* go, int flags);
	void DragAndDrop(GameObject* go);

	//Inspector
	void SetPosition(const float3& newPosition);
	void SetScale(const float3& newScale);
	void SetRotation(const float3& newRotation);

	float4x4 transformMatrix;
	float4x4 transformMatrixLocal;

private:

	EngineSystem* engineSystem;

	GameObject* ghostObject = nullptr;

	//GameObject* gameObject = nullptr;
	GameObject* selectedGameObject = nullptr;
	GameObject* destinationGameObject = nullptr;
	std::vector<GameObject*> selectedGameObjects;
	bool is_selected = false;

	Frustum frustum;
	
	float3 position;
	Quat rotation;

	/*true = editing in WORLD mode
	false = editing in LOCAL mode*/
	bool editingModeWorld = true;
};
