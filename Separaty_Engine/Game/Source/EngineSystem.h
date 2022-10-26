#pragma once

#include "Globals.h"
#include "Module.h"

#include "Scene.h"
#include "GameObject.h"
#include "GameObjComponent.h"

class Scene;

class EngineSystem : public Module
{
public:
	EngineSystem();
	~EngineSystem();


	bool Start();
	bool Init();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	bool LoadScene();
	bool CreateNewScene();

	std::vector<Scene*> GetSceneList() const
	{
		return scenes;
	}



	Scene* GetCurrentScene() const;


	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	GameObject* CreateNewGameObject();
	GameObjectComponent* CreateNewGOC(GameObject* goAttached, GOC_Type type);
private:
	
	int scenes_id = 0;

	std::vector<Scene*> scenes;
	std::vector<GameObject*> allGameObjects;
	std::vector<GameObjectComponent*> allGameObjecComponents;

	Scene* currentScene;


};

