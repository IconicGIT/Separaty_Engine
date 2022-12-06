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
		selectedGameObjects = App->engineSystem->GetselectedGameObjects();

		ImGui::Begin("Hierarchy", &App->ui->hierarchy);
		windowSize = ImVec2(App->ui->screenX / 5.5f, App->ui->screenY - App->ui->screenY / 4 - 17.0);
		ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) * 0.0f, 18.9f));
		ImGui::SetWindowSize(windowSize);

		Scene* currentScene = App->engineSystem->GetCurrentScene();

		if (!currentScene->gameObjects.empty())
		{

			static bool alignLabelWithCurrentXPosition = false;

			if (alignLabelWithCurrentXPosition)
				ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());


			for (GameObject* go : currentScene->gameObjects)
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

				if (go->parent == nullptr) DisplayTree(go, flags);
			}

			if (alignLabelWithCurrentXPosition)
				ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		}

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

void Hierarchy::DisplayTree(GameObject* go, int flags)
{
	flags |= ImGuiTreeNodeFlags_Leaf;

	DragAndDrop(go);

	Scene* currentScene = App->engineSystem->GetCurrentScene();

	//if (go->parent != nullptr)
	//{
	//	ImGui::Dummy(ImVec2(5, 0));
	//	ImGui::SameLine();
	//}
	if (ImGui::TreeNode(go->name.c_str()))
	{
		//for (GameObject* sceneGo : App->engineSystem->GetCurrentScene()->gameObjects)
		//{
		//	sceneGo->selected = false;
		//}
		for (int i = 0; i < go->GetChildren().size(); i++)
		{
			DisplayTree(go->GetChildren()[i], flags);
		}

		selectedGameObjects.push_back(go);

		go->selected = true;


		ImGui::Dummy(ImVec2(8, 0));
		ImGui::SameLine();
		if (ImGui::MenuItem("Create Child", "", false, false))
		{
			//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
			//	{

			//		if (go->GetID() == go->selected && go->GetID() != -1)
			//		{
			//			/*go->Delete();*/
			//			go->selected = 0;

			//		}

			//	}
		}

		ImGui::Dummy(ImVec2(0, 0));
		ImGui::SameLine();
		if (ImGui::MenuItem("Delete", "", false, false))
		{
			//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
			//	{

			//		if (go->GetID() == go->selected && go->GetID() != -1)
			//		{
			//			/*go->Delete();*/
			//			go->selected = 0;

			//		}

			//	}
		}
		ImGui::TreePop();

	}
	else
	{
		go->selected = false;
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