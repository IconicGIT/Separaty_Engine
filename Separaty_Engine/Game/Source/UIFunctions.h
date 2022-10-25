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
	
	/*GameObject* CreateNewGameObject();*/
private:

	std::vector<GameObject*> gameObjects;
	EngineSystem* engineSystem;

};
