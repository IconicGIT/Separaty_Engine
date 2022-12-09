#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Assets.h"

#include "physFS/include/physfs.h"

#include <filesystem>

#include <gl/GL.h>
#include <gl/GLU.h>





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

		ImGui::Begin("Folder Explorer", &App->ui->assets);

		FolderExplorer();
		

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

void Assets::FolderExplorer()
{
	float padding = 16.0f;
	float iconSize = 96.0f;
	float cellSize = iconSize + padding;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	//if (currentDir != std::filesystem::path(assetsDir)) {
	//	if (ImGui::Button("<-")) {
	//		//setting current directory to its parent (the one before)
	//		currentDir = currentDir.parent_path();
	//	}
	//}
	ImGui::Columns(columnCount, 0, false);

	//for (auto& directoryEntry : std::filesystem::directory_iterator(currentDir)) {
	//	const auto& path = directoryEntry.path();
	//	auto relativePath = std::filesystem::relative(path, assetsDir);
	//	std::string filenameString = relativePath.filename().string();

	//	uint id = directoryEntry.is_directory() ? directoryTexture.id : fileTexture.id;
	//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	//	ImGui::ImageButton((ImTextureID)id, { iconSize,iconSize });
	//	ImGui::PopStyleColor();



	//	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
	//		if (directoryEntry.is_directory())
	//		{
	//			currentDir /= path.filename();
	//		}
	//		else {

	//			std::string ext = path.extension().string();
	//			if (ext == ".milk" || ext == ".cream" || ext == ".txt" || ext == ".glsl" || ext == ".mat") {

	//				editor->LoadFromPath(path.string());
	//				/*PanelTextEditor* panel = editor->GetPanel<PanelTextEditor>();
	//				panel->Focus();*/
	//			}
	//		}

	//	}
	//	if (ImGui::IsItemHovered() && (ImGui::IsMouseClicked(1) || ImGui::IsMouseClicked(0))) {
	//		if (!directoryEntry.is_directory()) {
	//			selectedFile = path.string();

	//		}
	//	}

	//	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
	//		std::string itemPath = selectedFile;
	//		ImGui::SetDragDropPayload("ASSETS_ITEM", itemPath.c_str(), itemPath.size() * sizeof(const char*));
	//		ImGui::Text(itemPath.c_str());
	//		ImGui::EndDragDropSource();
	//	}

	//	ImGui::TextWrapped(filenameString.c_str());
	//	ImGui::NextColumn();

	//}
	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1)) {
		ImGui::OpenPopup("File Handle");
	}
	ImGui::Columns(1);

	if (ImGui::BeginPopup("File Handle")) {

		if (ImGui::BeginMenu("Create")) {
			if (ImGui::MenuItem("Material")) {
				std::string fileName = FileExistsMaterial("/material.milk", 1);

				/*std::string path = currentDir.string() + fileName;*/
				/*editor->LoadFromPath(path.c_str());*/
			}
			if (ImGui::MenuItem("Shader")) {
				std::string fileName = FileExsistsShader("/shader.glsl", 1);

				/*std::string path = currentDir.string() + fileName;*/
				/*editor->LoadFromPath(path.c_str());*/
			}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Delete")) {
			/*std::filesystem::remove(selectedFile);*/
			selectedFile = "";
		}

		ImGui::EndPopup();
	}

	

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

std::string Assets::FileExistsMaterial(std::string fileName, int i)
{
	int j = i;
	std::string name = "";
	std::string number = "";
	std::string ext = "";
	/*if (std::filesystem::exists(currentDir.string() + fileName)) {
		name = "/material";
		number = std::to_string(j);
		ext = ".milk";
		return FileExistsMaterial(name + " (" + number + ") " + ext, j + 1);
	}
	else {
		return fileName;
	}*/
	return name + number + ext;
}

std::string Assets::FileExsistsShader(std::string fileName, int i)
{
	int j = i;
	std::string name = "";
	std::string number = "";
	std::string ext = "";
	/*if (std::filesystem::exists(currentDir.string() + fileName)) {
		name = "/shader";
		number = std::to_string(j);
		ext = ".glsl";
		return FileExsistsShader(name + " (" + number + ") " + ext, j + 1);
	}
	else {
		return fileName;
	}*/
	return name + number + ext;
}