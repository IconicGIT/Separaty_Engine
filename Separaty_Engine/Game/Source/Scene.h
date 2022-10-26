#pragma once

#include "Globals.h"
#include "Module.h"
#include "GameObject.h"

class EngineSystem;
class GameObject;

class Scene : public Module
{
public:
	Scene(EngineSystem *system, bool active = true);

	Scene(std::string name, uint id, EngineSystem* system, bool active = true);

	~Scene();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;
	
	GameObject* CreateNewGameObject();

	std::vector<GameObject*> GetGameObjectList() const
	{
		return gameObjects;
	}
private:

	std::string sceneName;
	bool active;
	std::vector<GameObject*> gameObjects;
	uint sceneID;
	EngineSystem * engineSystem;
};

