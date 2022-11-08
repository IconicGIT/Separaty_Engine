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


	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Models/baker_house.fbx");
	App->engineSystem->LoadFromPath((char*)"Assets/Project_1/Assets/Textures/checker_pattern.png");

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

	if (!App->engineSystem->GetAllMeshes().empty())
	{
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
		{
			//Mesh* m( &App->engineSystem->GetAllMeshes()[0]);

			goRenderer->SetMesh(&App->engineSystem->GetAllMeshes()[0]);

			int a = 0;
		}

		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
		{
			goRenderer->SetMesh(&App->engineSystem->GetAllMeshes()[1]);
		}
	}

	if (!App->engineSystem->GetAllTextures().empty())
	{
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
		{
			goRenderer->SetTexture(&App->engineSystem->GetAllTextures()[0]);
		}

		if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
		{
			goRenderer->SetTexture(&App->engineSystem->GetAllTextures()[2]);
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

bool Scene::LoadState(JSON_Value* file)
{
	return true;

}

bool Scene::SaveState(JSON_Value* file) const
{
	return true;
}