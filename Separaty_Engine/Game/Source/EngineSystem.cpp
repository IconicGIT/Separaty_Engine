#include "EngineSystem.h"

EngineSystem::EngineSystem()
{
	name = "EngineSystem";
}

EngineSystem::~EngineSystem()
{
}

bool EngineSystem::Start()
{
	CreateNewScene();

	return true;
}

bool EngineSystem::Init()
{

	modelExtensionsAccepted.push_back("fbx");
	modelExtensionsAccepted.push_back("obj");

	imageExtensionsAccepted.push_back("png");
	imageExtensionsAccepted.push_back("jpg");

	return true;

}


update_status EngineSystem::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status EngineSystem::Update(float dt)
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

	if (App->input->FileJustDropped())
	{
		LoadFromDraggedData(App->input->GetDroppedFileDir());
	}

	return ret;
}
update_status EngineSystem::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;

}

bool EngineSystem::CleanUp()
{
	return true;

}

bool EngineSystem::LoadScene()
{
	return true;
}

bool EngineSystem::CreateNewScene()
{
	std::string scene_name = "scene " + std::to_string(scenes.size() + 1);

	Scene* scene = new Scene(scene_name, scenes_id, this);
	scene->Start();
	scenes.push_back(scene);

	currentScene = scene;

	return true;
}


Scene* EngineSystem::GetCurrentScene() const
{
	return currentScene;
}

GameObject* EngineSystem::CreateNewGameObject()
{
	std::string gameobject_name = "GameObject " + std::to_string(allGameObjects.size());

	GameObject* go = new GameObject(allGameObjects.size(), this);
	go->name = gameobject_name;
	go->Init();
	go->Start();
	allGameObjects.push_back(go);

	App->ui->AppendToOutput(DEBUG_LOG("Created GameObject, id: %i", go->GetID()));

	return go;
}

GameObjectComponent* EngineSystem::CreateNewGOC(GameObject* goAttached, GOC_Type type)
{
	
	switch (type)
	{
	case GOC_Type::GOC_MESH_RENDERER:
	{
		GOC_MeshRenderer* comp = new GOC_MeshRenderer(goAttached, goAttached->transform->Get4x4Matrix());
		allGameObjectComponents.push_back(comp);
		return comp;
	}
	break;
	default:
		break;
	}

	
}

bool EngineSystem::LoadModel(char* path)
{
	Model* modelToAdd = new Model(path);
	allModels.push_back(modelToAdd);

	App->ui->AppendToOutput(DEBUG_LOG("Loaded Model (%s)", path));


	//make gameobject when loading model

	return true;
}





bool EngineSystem::LoadFromDraggedData(char* draggedFileDir)
{
	bool ret = false;
	std::string sDraggedFileDir = draggedFileDir;
	

	int dotPos = sDraggedFileDir.find_last_of(".");

	std::string fileExtension = sDraggedFileDir.substr(dotPos + 1);

	int a;
	for (std::string ext : modelExtensionsAccepted)
	{
		a = strncmp(fileExtension.c_str(), ext.c_str(), fileExtension.length());
		if ( a == 0)
		{
			LoadModel(draggedFileDir);
			ret = true;

			return ret;
		}
	}

	for (int i = 0; i < imageExtensionsAccepted.size(); i++)
	{
		a = strncmp(fileExtension.c_str(), imageExtensionsAccepted[i].c_str(), fileExtension.length());
		if (a == 0)
		{
			int texToAdd = LoadTexture(draggedFileDir);
			allTextures.push_back(texToAdd);

			ret = true;

			App->ui->AppendToOutput(DEBUG_LOG("Loaded Texture (%s)", draggedFileDir));

			return ret;
		}
	}

	App->ui->AppendToOutput(DEBUG_LOG("Could not load file. File not supported (%s)", fileExtension.c_str()));
	

	return ret;
}


bool EngineSystem::LoadState(JSON_Value* file)
{
	return true;

}

bool EngineSystem::SaveState(JSON_Value* file) const
{
	return true;
}