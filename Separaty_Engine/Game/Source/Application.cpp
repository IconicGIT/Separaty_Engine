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
	

	
	// Scenes
	AddModule(scene_intro);

	// Renderer last!
	AddModule(renderer3D);
	AddModule(ui);
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

	float frameMaxSpeed = 1000.0f / window->maxFPS;
	if ((frameMaxSpeed - dt * 1000.f) > 0.0f)
	{
		SDL_Delay(fabs(floor((long)frameMaxSpeed - (float)ms_timer.Read())));
	}

	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{

	if (loadGameRequested == true)
	{
		LoadGame();
	}
	if (saveGameRequested == true)
	{
		SaveGame();
	}

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

void Application::RequestBrowser(const char* string)
{
	const char* link = string;
	ShellExecuteA(NULL, "open", link, NULL, NULL, SW_SHOWNORMAL);
}


// Load / Save
void Application::LoadGameRequest()
{
	bool ret = true;

	/*pugi::xml_document gameStateFile;
	pugi::xml_parse_result  result = gameStateFile.load_file("saveGame.xml");

	if (gameStateFile.child("saveState") == NULL)
		ret = false;
	*/

	loadGameRequested = ret;
}

// ---------------------------------------
bool Application::SaveGameRequest() const
{
	bool ret = false;

	saveGameRequested = true;


	return ret;
}

bool Application::LoadGame()
{
	bool ret = true;

	loadGameRequested = false;


	return ret;
}

bool Application::SaveGame() const
{
	bool ret = true;



	/*JSON_Value* schema = json_parse_string("{\"Separaty_Engine_Config\":\"\"}");
	JSON_Value* user_data = json_parse_file("Config.json");

	std::string a = "alberto";
	const char* buf = a.c_str();
	const char* name;

	user_data = json_value_init_object();
	json_object_set_string(json_object(user_data), "name", buf);
	json_serialize_to_file(user_data, "user_data.json");

	name = json_object_get_string(json_object(user_data), "name");
	printf("Hello, %s.", name);
	json_value_free(schema);
	json_value_free(user_data);*/

	JSON_Value* schema = json_parse_string("{\"Separaty_Engine_Config\":\"\"}");
	JSON_Value* config_file = json_parse_file("Config.json");

	// Call Init() in all modules
	Module* item = list_modules.front();
	int item_it = 0;

	while (item_it < list_modules.size() && ret == true)
	{
		item = list_modules[item_it];
		
		item->SaveState(config_file);


		item_it++;

	}

	App->ui->AppendToOutput(DEBUG_LOG("Saved."));

	saveGameRequested = false;

	return ret;
}

/*

// call all the modules to load themselves
bool App::LoadGame()
{
	loadingScreen = true;
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result result = gameStateFile.load_file(SAVE_STATE_FILENAME);
	//pugi::xml_parse_result result = gameStateFile.load_file("config.xml");
	if (result == NULL)
	{
		LOG("Could not load xml file savegame.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		p2ListItem<Module*>* item;
			item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->LoadState(gameStateFile.child("saveState").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	loadGameRequested = false;


	return ret;
}

// xml save method for current state
bool App::SaveGame() const
{
	bool ret = true;

	pugi::xml_document* saveDoc = new pugi::xml_document();
	pugi::xml_node  saveStateNode = saveDoc->append_child("saveState");

	p2ListItem<Module*>* item;
	item = modules.start;


	while (item != NULL)
	{
		if (item->data->toSave == true)
		{
			if (ret != item->data->SaveState(saveStateNode.append_child(item->data->name.GetString())))
				LOG("could not save status of %s", item->data->name.GetString());
		}

		item = item->next;
	}

	if (ret != saveDoc->save_file("saveGame.xml"))
		LOG("Could not save savegame file....");

	saveGameRequested = false;

	LOG("Game Saved...");

	return ret;
}

*/