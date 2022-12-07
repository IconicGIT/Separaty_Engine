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
			std::vector<std::string> directory;
			std::vector<std::string> file;

			std::string root_dir = roots;

			LookFiles(root_dir.c_str(), file, directory);

			for (size_t i = 0; i < directory.size(); i++)
			{
				std::string path = root_dir + directory[i] + ("/");

				if (ImGui::TreeNode(path.c_str(), 0, "%s/", directory[i].c_str()))
				{
					/*ResourceManagment(path.c_str(), extension_to_filter);*/
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
						sprintf_s(display, 200, "%s%s", root_dir.c_str(), file[i].c_str());
					}

					ImGui::TreePop();
				}
			}

			directory.clear();
			file.clear();
			root_dir.clear();

            ImGui::TreePop();
        }

        ImGui::End();
    }

    return UPDATE_CONTINUE;
}

void Assets::LookFiles(const char* directory, std::vector<std::string>& file_list, std::vector<std::string>& dir_list) const
{
	char** file_listing = PHYSFS_enumerateFiles(directory);									// Method that returns a listing with all the files in a given search path's directory.

	for (char** file = file_listing; *file != nullptr; ++file)								// Will iterate the file listing file per file.
	{
		std::string path = std::string(directory) + std::string("/") + std::string(*file);	// Will put together a path with the given directory and the file being currently iterated.

		if (PHYSFS_isDirectory(path.c_str()))
		{
			dir_list.push_back(*file);														// If the path is a directory, the file will be added to the directory list.
		}
		else
		{
			file_list.push_back(*file);														// If the path is not a directory, the file will be added to the file list.
		}
	}

	PHYSFS_freeList(file_listing);
}
