#include "Scene.h"



Scene::Scene(bool active)
{
	name = "_";
}

Scene::Scene(std::string name, bool active)
{
	this->name = name;
}

Scene::~Scene()
{
}

bool Scene::Start()
{

	App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));
	return true;

}

update_status Scene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	{
		App->ui->AppendToOutput(DEBUG_LOG(name.c_str()));
	}
	return UPDATE_CONTINUE;

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