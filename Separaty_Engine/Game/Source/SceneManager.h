#pragma once

#include "Globals.h"
#include "Module.h"

#include "GameObject.h"
#include "Scene.h"

class Scene;

class SceneManager : public Module
{
public:
	SceneManager();
	~SceneManager();


	bool Start();
	bool Init();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	bool LoadScene();
	bool CreateNewScene();



	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;



private:
	
	int scenes_id = 0;

	std::vector<Scene*> scenes;


};

