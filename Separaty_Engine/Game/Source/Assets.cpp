#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Assets.h"

#include "physFS/include/physfs.h"
#include <fstream>
#include <filesystem>




//ASSETS WINDOW

Assets::Assets()
{
	name = "Assets";

	display = new char[500];

	sprintf_s(display, 500, "%s", "Assets/");
}


Assets::~Assets()
{

}

update_status Assets::Update(float dt)
{
	if (App->ui->assets)
	{
		ImGui::Begin("Assets", &App->ui->assets, ImGuiWindowFlags_NoMove);

		if (ImGui::TreeNode("Assets/"))
		{
			ResourceManagment("Assets/", ".meta");

			ImGui::TreePop();
		}

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

void Assets::ResourceManagment(const char* roots, const char* extension_to_filter)
{

	std::vector<std::string> directory;
	std::vector<std::string> file;

	std::string root_dir = roots;

	/*LookFiles(root_dir.c_str(), file, directory);*/

	for (size_t i = 0; i < directory.size(); i++)
	{
		std::string path = root_dir + directory[i] + ("/");

		if (ImGui::TreeNode(path.c_str(), 0, "%s/", directory[i].c_str()))
		{
			ResourceManagment(path.c_str(), extension_to_filter);
			path.clear();
			ImGui::TreePop();
		}
	}


	std::sort(file.begin(), file.end());

	for (size_t i = 0; i < file.size(); ++i)
	{
		if (ImGui::TreeNode(file[i].c_str()))
		{
			if (ImGui::IsItemClicked())
			{
				sprintf_s(display, 500, "%s%s", root_dir.c_str(), file[i].c_str());
			}

			ImGui::TreePop();
		}
	}

	directory.clear();
	file.clear();
	root_dir.clear();

}

void Assets::LookFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& dir_list) const
{
	char** file_listing = PHYSFS_enumerateFiles(directory);

	for (char** file = file_listing; *file != nullptr; ++file)
	{
		std::string path = std::string(directory) + std::string("/") + std::string(*file);

		if (PHYSFS_isDirectory(path.c_str()))
		{
			dir_list.push_back(*file);
		}
		else
		{
			file_list.push_back(*file);
		}
	}

	PHYSFS_freeList(file_listing);
}
