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

	void ResourceManagment(const char* root_directory, const char* extension_to_filter);

	void LookFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& dir_list) const;

	const char* roots;
private:
	std::string name;

	char* display;
};