#pragma once

#include "Module.h"
#include "Globals.h"

class Editor;
struct EngineConfig;

class PlayStop : public Module
{
public:
	PlayStop();
	~PlayStop();

	update_status Update(float dt)override;

	bool play = false;

	float gameTime = 0.0f;
	float timeSpeed = 1.0f;
private:
	std::string name;

	
};