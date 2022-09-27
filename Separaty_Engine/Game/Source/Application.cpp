#include "Application.h"

Application::Application() : debug(false)
{
	window = new ModuleWindow();
	input = new ModuleInput();
	audio = new ModuleAudio();
	scene_intro = new ModuleSceneIntro();
	renderer3D = new ModuleRenderer3D();
	camera = new ModuleCamera3D();
	ui = new ModuleUI();

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(ui);

	
	// Scenes
	AddModule(scene_intro);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	Module* item = list_modules.back();
	int item_it = list_modules.size() - 1;

	while(item_it >= 0)
	{
		item = list_modules[item_it];
		list_modules.pop_back();
		item_it--;
	}
}

bool Application::Init()
{
	bool ret = true;

	App = this;

	// Call Init() in all modules
	Module* item = list_modules.front();
	int item_it = 0;

	while(item_it < list_modules.size() && ret == true)
	{
		item = list_modules[item_it];
		ret = item->Init();
		item_it++;
	
	}

	// After all Init calls we call Start() in all modules
	DEBUG_LOG("Application Start --------------");
	item = list_modules.front();
	item_it = 0;

	while (item_it < list_modules.size() && ret == true)
	{
		item = list_modules[item_it];
		ret = item->Start();
		item_it++;
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	Module* item = list_modules.front();
	int item_it = 0;

	while (item_it < list_modules.size() && ret == true)
	{
		item = list_modules[item_it];
		ret = item->PreUpdate(dt);
		item_it++;
	}

	item = list_modules.front();
	item_it = 0;

	while (item_it < list_modules.size() && ret == true)
	{
		item = list_modules[item_it];
		ret = item->Update(dt);
		item_it++;
	}

	item = list_modules.front();
	item_it = 0;

	while (item_it < list_modules.size() && ret == true)
	{
		item = list_modules[item_it];
		ret = item->PostUpdate(dt);
		item_it++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	Module* item = list_modules.back();
	int item_it = list_modules.size() - 1;

	while (item_it >= 0 && ret == true)
	{
		item = list_modules[item_it];
		ret = item->CleanUp();
		item_it--;
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

Application* App = nullptr;
