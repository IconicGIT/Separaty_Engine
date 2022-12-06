#pragma once

#include "Module.h"
#include "Globals.h"

class Editor;
struct EngineConfig;

class Output : public Module
{
public:
	Output();
	~Output();

	update_status Update(float dt)override;

private:
	std::string name;
};