#pragma once

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include "UIFunctions.h"

class GameObject;
class Editor;
class UIFunctions;
struct EngineConfig;

class Hierarchy : public Module
{
public:
	Hierarchy();
	~Hierarchy();

	update_status Update(float dt)override;

	void DisplayTree(GameObject* go, int flags);
	void DragAndDrop(GameObject* go);

	GameObject* selectedGameObject = nullptr;
	GameObject* destinationGameObject = nullptr;
	GameObject* p = nullptr;
	UIFunctions* UImanager;
private:
	std::string name;
};