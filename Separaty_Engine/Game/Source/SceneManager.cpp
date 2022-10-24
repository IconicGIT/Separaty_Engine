#include "SceneManager.h"

SceneManager::SceneManager()
{
	name = "SceneManager";
}

SceneManager::~SceneManager()
{
}

bool SceneManager::Start()
{

	return true;

}

bool SceneManager::Init()
{
	return true;

}


update_status SceneManager::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;

}

update_status SceneManager::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == true)
		{
			item = scenes[item_it];
			ret = item->PreUpdate(dt);
			item_it++;
		}

		item = scenes.front();
		item_it = 0;

		while (item_it < scenes.size() && ret == true)
		{
			item = scenes[item_it];
			ret = item->Update(dt);
			item_it++;
		}

		item = scenes.front();
		item_it = 0;

		while (item_it < scenes.size() && ret == true)
		{
			item = scenes[item_it];
			ret = item->PostUpdate(dt);
			item_it++;
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		CreateNewScene();
	}

	return ret;
}
update_status SceneManager::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;

}

bool SceneManager::CleanUp()
{
	return true;

}

bool SceneManager::LoadScene()
{
	return true;
}

bool SceneManager::CreateNewScene()
{
	std::string scene_name = "scene " + std::to_string(scenes_id);
	scenes_id++;

	Scene* scene = new Scene(scene_name, scenes_id);
	scene->Start();
	scenes.push_back(scene);

	return true;
}


bool SceneManager::LoadState(JSON_Value* file)
{
	return true;

}

bool SceneManager::SaveState(JSON_Value* file) const
{
	return true;
}