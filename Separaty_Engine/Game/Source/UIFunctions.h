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

	void DisplayTree(GameObject* go, int flags);
	void DragAndDrop(GameObject* go);

private:

	EngineSystem* engineSystem;

	Application* app = nullptr;
	GameObject* gameObject = nullptr;
	GameObject* selectedGameObject = nullptr;
	GameObject* destinationGameObject = nullptr;
	bool is_selected = false;

};
