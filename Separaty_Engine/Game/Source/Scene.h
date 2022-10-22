#pragma once

#include "Globals.h"
#include "Module.h"
#include "GameObject.h"


class Scene : public Module
{
public:
	Scene(bool active = true);

	Scene(std::string name, bool active = true);

	~Scene();


	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;
	
private:

	std::string sceneName;
	bool active;
};

