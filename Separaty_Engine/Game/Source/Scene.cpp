#include "Scene.h"



Scene::Scene(bool active)
{
	name = "_";
}

Scene::Scene(std::string name, uint id, bool active)
{
	this->name = name;
	this->sceneID = id;
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
		CreateNewGameObject();
	}

	return UPDATE_CONTINUE;

}


bool Scene::CreateNewGameObject()
{
	std::string gameobject_name = "GameObject  " + std::to_string(gameObjects.size());

	GameObject* go = new GameObject(gameObjects.size());
	go->name = gameobject_name;
	go->Init();
	go->Start();
	gameObjects.push_back(go);

	App->ui->AppendToOutput(DEBUG_LOG("Created GameObject, id: %i", go->GetID()));

	return true;
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