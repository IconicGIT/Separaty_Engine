#pragma once

#include "Module.h"
#include "Globals.h"

#include <filesystem>
#include <fstream>

class Editor;
struct EngineConfig;

struct TextureIcon {
	unsigned int id = 0;
	int width, height, nrChannels;
};

class Assets : public Module
{
public:
	Assets();
	~Assets();

	update_status Update(float dt)override;

	void ResourceManagment(const char* root_directory, const char* extension_to_filter);

	void LookFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& dir_list) const;

	void FolderExplorer();

	const char* roots;

	UIFunctions* UImanager;
private:
	std::string name;

	std::string FileExistsMaterial(std::string fileName, int i);
	std::string FileExsistsShader(std::string fileName, int i);

	EngineSystem* editor = nullptr;
	TextureIcon fileTexture;
	TextureIcon directoryTexture;
	std::string fileIcon, directoryIcon;
	/*const std::filesystem::path assetsDir = "Assets";
	std::filesystem::path currentDir = "Assets";*/
	std::string selectedFile = "";

	char* display;
};