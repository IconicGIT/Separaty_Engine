#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Hierarchy.h"


//HIERARCHY WINDOW

Hierarchy::Hierarchy()
{
	name = "Hierarchy";
}

Hierarchy::~Hierarchy()
{

}

update_status Hierarchy::Update(float dt)
{
	ImVec2 windowSize = ImVec2(0, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (App->ui->hierarchy)
	{
		UImanager->selectedGameObjects = App->engineSystem->GetselectedGameObjects();

		ImGui::Begin("Hierarchy", &App->ui->hierarchy, ImGuiWindowFlags_NoMove);
		windowSize = ImVec2(App->ui->screenX / 5.5f, App->ui->screenY - App->ui->screenY / 4 - 17.0);
		ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) * 0.0f, 18.9f));
		ImGui::SetWindowSize(windowSize);

		Scene* currentScene = App->engineSystem->GetCurrentScene();

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		if (!currentScene->gameObjects.empty())
		{

			static bool alignLabelWithCurrentXPosition = false;

			if (alignLabelWithCurrentXPosition)
				ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());


			for (size_t i = 0; i < currentScene->gameObjects.size(); i++)

			{
				

				if (currentScene->gameObjects[i]->selected)
				{
					//flags |= ImGuiTreeNodeFlags_DefaultOpen;

				}

				if (currentScene->gameObjects[i]->parent == nullptr)
				{
					
					

					DisplayTree(currentScene->gameObjects[i], flags);
				}
					
			}

			if (alignLabelWithCurrentXPosition)
				ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		}

		ImGui::End();
	}

	
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{

		App->ui->AppendToOutput(DEBUG_LOG("selected: %i", UImanager->selectedGameObjects.size()));
	}

	return UPDATE_CONTINUE;
}

void Hierarchy::DisplayTree(GameObject* go, int flags)
{
	//flags |= ImGuiTreeNodeFlags_Leaf;

	/*DragAndDrop(go);*/

	Scene* currentScene = App->engineSystem->GetCurrentScene();


	std::string hierarchyName = go->name + "##" + std::to_string(go->id);
	
		if (go->selected)
		{
			//flags |= ImGuiTreeNodeFlags_Leaf;
		}
	


	if (ImGui::TreeNode(hierarchyName.c_str()))
	{
		//for (GameObject* sceneGo : App->engineSystem->GetCurrentScene()->gameObjects)
		//{
		//	sceneGo->selected = false;
		//}

		if (ImGui::MenuItem("Delete"))
		{
			go->pendingToDelete = true;
		}

		for (int i = 0; i < go->GetChildren().size(); i++)
		{
			if (go->GetChildren()[i]->selected)
			{
				//flags |= ImGuiTreeNodeFlags_DefaultOpen;
			}
			DisplayTree(go->GetChildren()[i], flags);
		}

		if (!go->selected)
		{
			UImanager->selectedGameObjects.push_back(go);
			App->engineSystem->AddToGameObjectsSelected(go);
			go->selected = true;
		}

		

		ImGui::Dummy(ImVec2(8, 0));
		ImGui::SameLine();
		if (ImGui::MenuItem("Create Child"))
		{
			go->CreateChildren();
		}




		
		ImGui::TreePop();

	}
	else
	{
		if (go->selected)
		{
			App->engineSystem->RemoveFromGameObjectsSelected(go);
			go->selected = false;
		}

	}
}



void Hierarchy::DragAndDrop(GameObject* go)
{
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("Hierarchy", go, sizeof(GameObject));
		selectedGameObject = go;
		ImGui::Text(go->name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Hierarchy");
		if (payload != nullptr)
		{
			if (selectedGameObject != nullptr)
			{
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly))
				{
					destinationGameObject = go;
					destinationGameObject->AttachChild(selectedGameObject);
					selectedGameObject = nullptr;
					destinationGameObject = nullptr;
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}