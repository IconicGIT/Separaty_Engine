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

	App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));

	GameObject* go = CreateNewGameObject();

	goRenderer = (GOC_MeshRenderer*)go->GetComponent(GOC_Type::GOC_MESH_RENDERER);

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

	if (!App->engineSystem->allMeshes.empty())
	{
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
		{
			goRenderer->SetMesh(&App->engineSystem->allMeshes[0]);
		}

		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
		{
			goRenderer->SetMesh(&App->engineSystem->allMeshes[1]);
		}
	}

	if (!App->engineSystem->allTextures.empty())
	{
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
		{
			goRenderer->SetTexture(&App->engineSystem->allTextures[0]);
		}

		if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
		{
			goRenderer->SetTexture(&App->engineSystem->allTextures[2]);
		}
	}

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