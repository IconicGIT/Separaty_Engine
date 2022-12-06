#pragma once

#include "Module.h"
#include "Globals.h"

class Editor;
struct EngineConfig;

class AppData : public Module
{
public:
	AppData();
	~AppData();

	update_status Update(float dt)override;

private:
	std::string name;
};