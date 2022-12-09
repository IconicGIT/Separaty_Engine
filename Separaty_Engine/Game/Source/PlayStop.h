#pragma once

#include "Module.h"
#include "Globals.h"

#include <time.h>

class Editor;
struct EngineConfig;

class PlayStop : public Module
{
public:
	PlayStop();
	~PlayStop();

	update_status Update(float dt)override;

	bool play = false;
	bool pause = false;

	float gameTime = 0.0f;
	float timeSpeed = 1.0f;
private:
	std::string name;

	float	hours;
	float	minutes;
	float	seconds = 0.0f;

	//std::string GetTimeAsString();

	
};