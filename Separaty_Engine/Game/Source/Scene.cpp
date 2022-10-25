#include "Scene.h"



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


	App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));

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
	return ret;
}



update_status Scene::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	if (!gameObjects.empty())
	{

		Module* item = gameObjects.front();
		int item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->PreUpdate(dt);
			item_it++;
		}

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->Update(dt);
			item_it++;
		}

		item = gameObjects.front();
		item_it = 0;

		while (item_it < gameObjects.size() && ret == true)
		{
			item = gameObjects[item_it];
			ret = item->PostUpdate(dt);
			item_it++;
		}
	}

	//if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	//{
	//	App->ui->AppendToOutput(DEBUG_LOG(name.c_str()));
	//}

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		GameObject* go = CreateNewGameObject();

		go->transform->SetPos(0, 0, go->GetID());

		
	}

	return UPDATE_CONTINUE;

}


GameObject* Scene::CreateNewGameObject()
{
	GameObject* go = engineSystem->CreateNewGameObject();

	gameObjects.push_back(go);

	return go;
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