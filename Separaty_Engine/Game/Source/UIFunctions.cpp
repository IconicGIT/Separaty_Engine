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
	ghostObject = App->engineSystem->CreateNewGameObject();
}

UIFunctions::~UIFunctions()
{

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

	assetsWindow = new Assets();
	assetsWindow->Start();

	outputWindow = new Output();
	outputWindow->Start();

	return true;
}

update_status UIFunctions::Update(float dt)
{
	//PROJECT PREFERENCES
	showPreferences->Update(dt);
	
	//App DATA 
	showApplicationData->Update(dt);

	//WINDOWS 
	ImGuiIO& io = ImGui::GetIO();
	
	hierarchyWindow->Update(dt);

	inspectorWindow->Update(dt);

	assetsWindow->Update(dt);

	outputWindow->Update(dt);


	//NO SE QUE QUERRAS HACER CON LAS PRIMITIVES, DE MOMENTO LAS DEJO AQUI, PORQUE AUN SE TIENEN QUE MDOIFICAR Y DEMAS.
	//YA MIRAREMOS DESPUES DE METERLAS EN OTRO LADO

	//PRIMITIVES
	if (App->ui->createEmptyObject)
	{
		App->engineSystem->GetCurrentScene()->CreateNewGameObject();

		App->ui->createEmptyObject = false;
	}
	if (App->ui->createCube)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cube.fbx");

		App->ui->createCube = false;
	}
	if (App->ui->createSphere)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Sphere.fbx");

		App->ui->createSphere = false;
	}
	if (App->ui->createCapsule)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Capsule.fbx");

		App->ui->createCapsule = false;
	}
	if (App->ui->createCylinder)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cylinder.fbx");

		App->ui->createCylinder = false;
	}
	if (App->ui->createPyramid)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Pyramid.fbx");

		App->ui->createPyramid = false;
	}
	if (App->ui->createCone)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cone.fbx");

		App->ui->createCone = false;
	}
	if (App->ui->createPlane)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Plane.fbx");

		App->ui->createPlane = false;
	}

	if (App->ui->cleanPrimitives)
	{
		App->ui->createCube = false;
		App->ui->createSphere = false;
		App->ui->createCapsule = false;
		App->ui->createCylinder = false;
		App->ui->createPlane = false;

		App->ui->cleanPrimitives = false;
	}

	//App->ui->AppendToOutput(DEBUG_LOG("selected size: %i", selectedGameObjects.size()));
	return UPDATE_CONTINUE;
}