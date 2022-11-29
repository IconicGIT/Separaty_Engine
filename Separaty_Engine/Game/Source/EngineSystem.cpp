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
	bool ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->Start();
			item_it++;
		}
	}

	currentScene = CreateNewScene();
	currentScene->Start();

	return true;
}

bool EngineSystem::Init()
{
	bool ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->Init();
			item_it++;
		}
	}

	modelExtensionsAccepted.push_back("fbx");
	modelExtensionsAccepted.push_back("obj");

	imageExtensionsAccepted.push_back("png");
	imageExtensionsAccepted.push_back("jpg");
	imageExtensionsAccepted.push_back("bmp");


	


	return ret;

}


update_status EngineSystem::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->PreUpdate(dt);
			item_it++;
		}
	}

	return UPDATE_CONTINUE;
}

update_status EngineSystem::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{
		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->Update(dt);
			item_it++;
		}

	}

	if (App->input->FileJustDropped())
	{
		LoadFromPath(App->input->GetDroppedFileDir());
	}

	return ret;
}
update_status EngineSystem::PostUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;

	if (!scenes.empty())
	{

		Module* item = scenes.front();
		int item_it = 0;

		while (item_it < scenes.size() && ret == UPDATE_CONTINUE)
		{
			item = scenes[item_it];
			ret = item->PostUpdate(dt);
			item_it++;
		}

	}

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

Scene* EngineSystem::CreateNewScene()
{
	std::string scene_name = "scene " + std::to_string(scenes.size() + 1);

	Scene* scene = new Scene(scene_name, scenes_id, this);
	scene->Init();
	scenes.push_back(scene);


	return scene;
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
	case GOC_Type::GOC_TEXTURE:
	{
		GOC_Texture* comp = new GOC_Texture(goAttached);
		allGameObjectComponents.push_back((GOC_Texture*)comp);
		return (GOC_Texture*)comp;
	}
	break;
	default:
		break;
	}

	
}

bool EngineSystem::LoadModel(char* path)
{
	std::string path_s = path;
	
	int lastBar = path_s.find_last_of("\\\"");
	if (lastBar == -1)
	{
		lastBar = path_s.find_last_of("/");
	}
	else
		return false;

	std::string name = path_s.substr(lastBar + 1);


	Model* modelToAdd = new Model(path);
	GameObject* go = App->engineSystem->currentScene->CreateNewGameObject();

	GOC_MeshRenderer* renderer = nullptr;

	int meshNr = 0;

	if (modelToAdd->GetMeshes().size() > 1)
	{
		for (Mesh mesh : modelToAdd->GetMeshes())
		{
			mesh.name = name;

			App->ui->AppendToOutput(DEBUG_LOG("Loaded Mesh %s", mesh.name.c_str()));

			GameObject* meshGo = go->CreateChildren();
			std::string meshGoName = mesh.name + std::to_string(meshNr);
			meshGo->name = meshGoName;

			renderer = (GOC_MeshRenderer*)meshGo->GetComponent(GOC_Type::GOC_MESH_RENDERER);
			renderer->SetMesh(&mesh);
			renderer->SetTextures(mesh.textures);



			allMeshes.push_back(mesh);
			meshNr++;
		}
	}
	else
	{
		Mesh mesh = modelToAdd->GetMeshes()[0];
		mesh.name = name;

		App->ui->AppendToOutput(DEBUG_LOG("Loaded Mesh %s", mesh.name.c_str()));

		std::string meshGoName = mesh.name + std::to_string(meshNr);
		go->name = meshGoName;

		renderer = (GOC_MeshRenderer*)go->GetComponent(GOC_Type::GOC_MESH_RENDERER);
		renderer->SetMesh(&mesh);
		renderer->SetTextures(mesh.textures);


		
		allMeshes.push_back(mesh);
	}

	
	meshNr = 0;
	for (size_t i = 0; i < modelToAdd->GetTextures().size(); i++)
	{
		modelToAdd->GetTextures()[i].name = name + " " + std::to_string(meshNr);

		allTextures.push_back(modelToAdd->GetTextures()[i]);

		App->ui->AppendToOutput(DEBUG_LOG("Loaded Texture %s", modelToAdd->GetTextures()[i].name.c_str()));
		meshNr++;
	}


	App->ui->AppendToOutput(DEBUG_LOG("Loaded Model (%s)", path));


	delete modelToAdd;

	//make gameobject when loading model

	return true;
}


bool EngineSystem::LoadFromPath(char* draggedFileDir)
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
			std::string path_s = draggedFileDir;
			int lastBar = path_s.find_last_of("\\\"");
			if (lastBar == -1)
			{
				lastBar = path_s.find_last_of("/");
			}

			std::string name = path_s.substr(lastBar + 1);

			Texture tex = LoadTexture(draggedFileDir);

			tex.name = name;

			allTextures.push_back(tex);

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