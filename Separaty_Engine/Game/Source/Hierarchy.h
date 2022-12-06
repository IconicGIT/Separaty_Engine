#pragma once

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"

class GameObject;
class Editor;
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
	std::vector<GameObject*> selectedGameObjects;

private:
	std::string name;
};