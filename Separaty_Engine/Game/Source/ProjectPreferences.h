#pragma once

#include "Module.h"
#include "Globals.h"

class Editor;
struct EngineConfig;

class Preferences : public Module
{
public:
	Preferences();
	~Preferences();

	update_status Update(float dt)override;

private:
	std::string name;
};