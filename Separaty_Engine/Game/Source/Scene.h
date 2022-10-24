#pragma once

#include "Globals.h"
#include "Module.h"
#include "GameObject.h"

class GameObject;

class Scene : public Module
{
public:
	Scene(bool active = true);

	Scene(std::string name, uint id, bool active = true);

	~Scene();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;
	
	bool CreateNewGameObject();
private:

	std::string sceneName;
	bool active;
	std::vector<GameObject*> gameObjects;
	uint sceneID;
};

