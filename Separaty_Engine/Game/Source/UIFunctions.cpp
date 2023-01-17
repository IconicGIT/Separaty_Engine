#include "Globals.h"
#include "Application.h"
#include "UIFunctions.h"
#include "GameObject.h"
#include "GameObjComponent.h"
#include "GOC_Transform.h"
#include "GOC_MeshRenderer.h"
#include "GOC_Texture.h"
#include "GOC_Camera.h"

#include "imgui_stdlib.h"
#include "scene.h"

#include "EngineSystem.h"

#include "ModuleUI.h"

std::string WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

UIFunctions::UIFunctions()
{
	
}

UIFunctions::~UIFunctions()
{

}

bool UIFunctions::Init()
{

	ghostObject = App->engineSystem->CreateNewGameObject();

	return true;
}

bool UIFunctions::Start()
{
	showPreferences = new Preferences();
	showPreferences->Start();

	showApplicationData = new AppData();
	showApplicationData->Start();

	hierarchyWindow = new Hierarchy();
	hierarchyWindow->UImanager = this;
	hierarchyWindow->Start();

	inspectorWindow = new Inspector();
	inspectorWindow->UImanager = this;
	inspectorWindow->Start();

	playStopWindow = new PlayStop();
	playStopWindow->Start();

	playStopIndividualWindow = new PlayStopIndividual();
	playStopIndividualWindow->Start();

	assetsWindow = new Assets();
	assetsWindow->Start();

	outputWindow = new Output();
	outputWindow->Start();

	

	return true;
}

update_status UIFunctions::Update(float dt)
{

	for (size_t i = 0; i < selectedGameObjects.size(); i++)
	{
		if (!selectedGameObjects[i]->selected)
			selectedGameObjects.erase(selectedGameObjects.begin() + i);
	}


	//PROJECT PREFERENCES
	showPreferences->Update(dt);
	
	//App DATA 
	showApplicationData->Update(dt);

	//WINDOWS 
	ImGuiIO& io = ImGui::GetIO();
	
	hierarchyWindow->Update(dt);

	inspectorWindow->Update(dt);

	playStopWindow->Update(dt);

	playStopIndividualWindow->Update(dt);

	assetsWindow->Update(dt);

	outputWindow->Update(dt);

	//PRIMITIVES
	if (App->ui->createEmptyObject)
	{
		App->engineSystem->GetCurrentScene()->CreateNewGameObject();
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createEmptyObject = false;
	}
	if (App->ui->createCube)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cube.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createCube = false;
	}
	if (App->ui->createSphere)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Sphere.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createSphere = false;
	}
	if (App->ui->createCapsule)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Capsule.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createCapsule = false;
	}
	if (App->ui->createCylinder)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cylinder.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createCylinder = false;
	}
	if (App->ui->createPyramid)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Pyramid.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createPyramid = false;
	}
	if (App->ui->createCone)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cone.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createCone = false;
	}
	if (App->ui->createPlane)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Plane.fbx");
		GameObject* go = App->engineSystem->GetCurrentScene()->GetGameObjectList()[App->engineSystem->GetCurrentScene()->GetGameObjectList().size() - 1];
		GOC_Texture* tex = nullptr;
		tex = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		tex->SetTexture(App->engineSystem->GetAllTextures()[0]);
		tex->UpdateMeshRendererTexture();

		App->ui->createPlane = false;
	}

	//if (App->ui->cleanPrimitives)
	//{
	//	App->ui->createCube = false;
	//	App->ui->createSphere = false;
	//	App->ui->createCapsule = false;
	//	App->ui->createCylinder = false;
	//	App->ui->createPlane = false;

	//	App->ui->cleanPrimitives = false;
	//}

	//App->ui->AppendToOutput(DEBUG_LOG("selected size: %i", selectedGameObjects.size()));
	return UPDATE_CONTINUE;
}

void UIFunctions::EraseFromSelectedGoList(GameObject* toErase)
{
	for (size_t i = 0; i < selectedGameObjects.size(); i++)
	{
		if (selectedGameObjects[i]->GetID() == toErase->GetID())
		{
			selectedGameObjects.erase(selectedGameObjects.begin() + i);
		}
	}
}