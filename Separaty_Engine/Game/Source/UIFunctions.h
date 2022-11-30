#pragma once

#include "ModuleUI.h"
#include "Globals.h"
#include "GameObject.h"

class EngineSystem;
class GameObject;

//class ModuleUI;
class Module;

class UIFunctions : public Module
{
public:

	UIFunctions();

	~UIFunctions();

	update_status Update(float dt) override;

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

	float3 position;
	Quat rotation;
	float3 rotationEuler;
	float3 scale;
};
