#include "Scene.h"

#include "ModuleUI.h"



Scene::Scene(EngineSystem *system, bool active)
{
	name = "_";
	this->engineSystem = system;
}

Scene::Scene(std::string name, uint id, EngineSystem* system, bool active)
{
	this->name = name;
	this->sceneID = id;
	this->engineSystem = system;

}

Scene::~Scene()
{
}


bool Scene::Init()
{
	bool ret = true;


	if (!gameObjects.empty())
	{
		// Call Init() in all modules
		GameObject* item = gameObjects.front();
		int item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->Init();
			item_it++;
		}
	}


	return ret;
}

bool Scene::Start()
{
	bool ret = true;


	// Call Start() in all gameobjects
	if (!gameObjects.empty())
	{
		GameObject* item = gameObjects.front();
		int item_it = 0;

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->Start();
			item_it++;
		}
	}

	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/default_texture.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/checker_pattern.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/baker_house.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/baker_house.fbx");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/baker_house.fbx");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/baker_house.fbx");

	/*App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/Street_environment_V01.FBX");

	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building-01_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building-06_c-.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building-06_-c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_016_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_025_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building03_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building05-_c.png");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_V02_C.png");*/


	GameObject* camera = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	camera->AddComponent(GOC_Type::GOC_CAMERA);
	camera->name = "Camera";

	GameObject* go = gameObjects[0];
	go->transform->translationLocal.translate(20, 0, 15);
	go->transform->ApplyTransformations();

	go = gameObjects[3];
	go->transform->translationLocal.translate(-20, 0, 15);
	go->transform->ApplyTransformations();

	go = gameObjects[6];
	go->transform->translationLocal.translate(0, 0, 15);
	go->transform->ApplyTransformations();


	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Capsule.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cone.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cube.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cylinder.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Plane.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Pyramid.fbx", false);
	App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Sphere.fbx", false);

	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/street2.FBX");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building 01_c.tga");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building 06_c .tga");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building 06_ c.tga");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_016_c.tga");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building_025_c.tga");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building03_c.tga");
	//App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/building05 _c.tga");


	for (GameObject* go : gameObjects)
	{
		GOC_Texture* texture = nullptr;
		texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
		texture->SetTexture(App->engineSystem->GetAllTextures()[2]);
		texture->UpdateMeshRendererTexture();
	}


	//
	//GOC_Texture* texture = nullptr;

	//go = gameObjects[9];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[4]);
	//texture->UpdateMeshRendererTexture();

	//go->transform->translationLocal.translate(19.15, 0, 23);
	//go->transform->ApplyTransformations();


	//go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
	//go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

	//go->transform->ApplyTransformations();

	////Game Object 10

	//go = gameObjects[10];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[7]);
	//texture->UpdateMeshRendererTexture();
	// 
	//go->transform->translationLocal.translate(19.15, 0, -27);
	//

	//go->transform->rotationLocal[0] = 0;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 1;
	//go->transform->rotationLocal[4] = 1;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = 0;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;
	//
	//go->transform->ApplyTransformations();

	////Game Object 11

	//go = gameObjects[11];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[9]);
	//texture->UpdateMeshRendererTexture();
	//
	//go->transform->translationLocal.translate(19.15, 0, 23);
	//go->transform->ApplyTransformations();


	//go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
	//go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;
	//
	//go->transform->ApplyTransformations();

	////Game Object 12

	//go = gameObjects[12];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[5]);
	//texture->UpdateMeshRendererTexture();

	//go->transform->translationLocal.translate(38, 0, 18.20);
	//go->transform->ApplyTransformations();


	//go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
	//go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

	//go->transform->ApplyTransformations();

	////Game Object 13

	//go = gameObjects[13];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[5]);
	//texture->UpdateMeshRendererTexture();

	//go->transform->translationLocal.translate(38, 0, 18.20);
	//go->transform->ApplyTransformations();


	//go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
	//go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

	//go->transform->ApplyTransformations();

	////Game Object 14

	//go = gameObjects[14];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[5]);
	//texture->UpdateMeshRendererTexture();

	//go->transform->translationLocal.translate(0, 0, 0);
	//go->transform->ApplyTransformations();


	//go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
	//go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

	//go->transform->ApplyTransformations();

	////Game Object 15

	//go = gameObjects[15];
	//texture = (GOC_Texture*)go->GetComponent(GOC_Type::GOC_TEXTURE);
	//texture->SetTexture(App->engineSystem->GetAllTextures()[5]);
	//texture->UpdateMeshRendererTexture();

	//go->transform->translationLocal.translate(0, 0, 0);
	//go->transform->ApplyTransformations();


	//go->transform->rotationLocal[0] = 1;		go->transform->rotationLocal[1] = 0;		go->transform->rotationLocal[2] = 0;
	//go->transform->rotationLocal[4] = 0;		go->transform->rotationLocal[5] = 0;		go->transform->rotationLocal[6] = -1;
	//go->transform->rotationLocal[8] = 0;		go->transform->rotationLocal[9] = 1;		go->transform->rotationLocal[10] = 0;

	//go->transform->ApplyTransformations();


	App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));

	return ret;
}



update_status Scene::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	if (!gameObjects.empty())
	{

		Module* item = gameObjects.front();
		int item_it = 0;

		while (item_it < gameObjects.size() && ret == true && item->enabled)
		{
			item = gameObjects[item_it];
			ret = item->PreUpdate(dt);
			item_it++;
		}

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true && item->enabled)
		{
			item = gameObjects[item_it];
			ret = item->Update(dt);
			item_it++;
		}

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true && item->enabled)
		{
			item = gameObjects[item_it];
			ret = item->PostUpdate(dt);
			item_it++;
		}
	}


	//if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
	//{


	//	std::string path = "C:\\Users\\Brandon AM\\Documents\\GitHub\\Separaty_Engine\\Separaty_Engine\\Output\\Assets\\Project_1\\Assets\\Models\\baker_house.fbx";

	//	char* path_c = new char(path.length() + 1);

	//	strncpy_s(path_c, 512, path.c_str(), path.length());

	//	//load baker_house and its textures
	//	App->engineSystem->LoadFromPath(path_c);

	//	path = "Assets/Project_1/Assets/Textures/checker_pattern.png";
	//	strncpy_s(path_c, 512, path.c_str(), path.length());

	//	//load checker_pattern
	//	App->engineSystem->LoadFromPath(path_c);


	//	GameObject* houseAll = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	//	GameObject* house = houseAll->CreateChildren();
	//	GameObject* chimney = houseAll->CreateChildren();


	//	goRenderer = (GOC_MeshRenderer*)house->GetComponent(GOC_Type::GOC_MESH_RENDERER);

	//	goRenderer->SetMesh(&App->engineSystem->GetAllMeshes()[1]);
	//	goRenderer->SetTexture(&App->engineSystem->GetAllTextures()[0]);

	//	goRenderer = (GOC_MeshRenderer*)chimney->GetComponent(GOC_Type::GOC_MESH_RENDERER);

	//	goRenderer->SetMesh(&App->engineSystem->GetAllMeshes()[0]);
	//	goRenderer->SetTexture(&App->engineSystem->GetAllTextures()[1]);

	//	delete path_c;
	//	loadedBasics = true;
	//}

	/*if (App->ui->createCube == true)
	{
		GameObject* go = CreateNewGameObject();

		go->transform->SetPos(0, 0, go->GetID());

	}*/

	return UPDATE_CONTINUE;

}


GameObject* Scene::CreateNewGameObject()
{
	GameObject* go = engineSystem->CreateNewGameObject();

	gameObjects.push_back(go);

	return go;
}

GameObject* Scene::GetSelectedGameObject()
{
	for (GameObject* go : gameObjects)
	{
		if (go->selected)
		{
			return go;
		}
	}

	return nullptr;
}

bool Scene::CleanUp()
{
	return true;

}

bool Scene::SaveState(JSON_Value* file) const
{
	for (GameObject* go : gameObjects)
	{
		if (go->parent == nullptr)
		{
			go->SaveState(file);
		}
		
	}

	return true;
}
bool Scene::LoadState(JSON_Value* file)
{
	for (GameObject* go : gameObjects)
	{
		if (go->parent == nullptr)
		{
			go->LoadState(file);
		}
	}

	return true;
}

