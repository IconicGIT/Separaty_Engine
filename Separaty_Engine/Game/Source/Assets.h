#pragma once

#include "Module.h"
#include "Globals.h"

class Editor;
struct EngineConfig;

class Assets : public Module
{
public:
	Assets();
	~Assets();

	update_status Update(float dt)override;

private:
	std::string name;
};