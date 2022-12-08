#include "GameObject.h"


GameObject::GameObject(uint id, EngineSystem* system, bool start_enabled)
{
	this->id = id;
	this->engineSystem = system;
}

GameObject::~GameObject()
{

}

bool GameObject::Init()
{
	transform = new GOC_Transform(this); 
	components.push_back(transform);
	return true;
}

bool GameObject::Start()
{
	AddComponent(GOC_Type::GOC_MESH_RENDERER);
	AddComponent(GOC_Type::GOC_TEXTURE);

	std::vector<Vertex> vertices;
	vertices.push_back((Vertex)(vec3(1.0, 1.0, 1.0)));
	vertices.push_back((Vertex)(vec3(0.0f, 1.0, 1.0)));
	vertices.push_back((Vertex)(vec3(1.0, 1.0, 0.0f)));
	vertices.push_back((Vertex)(vec3(0.0f, 1.0, 0.0f)));
	vertices.push_back((Vertex)(vec3(1.0, 0.0f, 1.0)));
	vertices.push_back((Vertex)(vec3(0.0f, 0.0f, 1.0)));
	vertices.push_back((Vertex)(vec3(0.0f, 0.0f, 0.0f)));
	vertices.push_back((Vertex)(vec3(1.0, 0.0f, 0.0f)));
	

	std::vector<uint> indices = {  // note that we start from 0!
		3, 2, 6, 7, 4, 2, 0,
		3, 1, 6, 5, 4, 1, 0
	};

	GOC_MeshRenderer* meshRenderer =  (GOC_MeshRenderer*)GetComponent(GOC_Type::GOC_MESH_RENDERER);

	Mesh* mesh = new Mesh(vertices, indices);

	//meshRenderer->SetMesh(mesh);

	return true;
}

update_status GameObject::Update(float dt)
{
	bool ret = UPDATE_CONTINUE;

	GameObjectComponent* item = components.front();
	int item_it = 0;

	while (item_it < components.size() && ret == true)
	{
		item = components[item_it];
		ret = item->Execute();
		item_it++;
	}

	/*if (parent != nullptr)
	{
		transform->SetPos(parent->transform->GetPosition().x + transform->GetPosition().x,
			parent->transform->GetPosition().y + transform->GetPosition().y,
			parent->transform->GetPosition().z + transform->GetPosition().z);

		transform->SetScale(parent->transform->GetScale().x * transform->GetScale().x,
			parent->transform->GetScale().y * transform->GetScale().y,
			parent->transform->GetScale().z * transform->GetScale().z);

	}*/

	/*if (!children.empty())
	{
		for (GameObject* child : children)
		{
			child->transform->SetPos(transform->GetPosition().x + child->transform->GetPosition().x,
				transform->GetPosition().y + child->transform->GetPosition().y,
				transform->GetPosition().z + child->transform->GetPosition().z);

			child->transform->SetScale(transform->GetScale().x * child->transform->GetScale().x,
				transform->GetScale().y * child->transform->GetScale().y,
				transform->GetScale().z * child->transform->GetScale().z);
		}
	}*/


	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate(float dt)
{
	/*RenderAxis();*/

	return UPDATE_CONTINUE;
}

bool GameObject::CleanUp()
{
	bool ret = UPDATE_CONTINUE;

	GameObjectComponent* item = components.front();
	int item_it = 0;

	while (item_it < components.size() && ret == true)
	{
		item = components[item_it];
		delete item;
		item_it++;
	}

	return true;
}


bool GameObject::SaveState(JSON_Value* file) const
{
	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), "gameObjects", buf);
	json_serialize_to_file(file, "Config.json");

	json_object_dotset_number(json_object(file), std::string(name + " Position.x").c_str(), (double)transform->translationLocal.translation().x);
	json_object_dotset_number(json_object(file), std::string(name + " Position.y").c_str(), (double)transform->translationLocal.translation().y);
	json_object_dotset_number(json_object(file), std::string(name + " Position.z").c_str(), (double)transform->translationLocal.translation().z);

	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.x", (double).x);
	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.y", (double)X.y);
	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.z", (double)X.z);

	json_object_dotset_number(json_object(file), "object.Scale.x", (double)transform->scalingLocal.scaling().x);
	json_object_dotset_number(json_object(file), "object.Scale.y", (double)transform->scalingLocal.scaling().y);
	json_object_dotset_number(json_object(file), "object.Scale.z", (double)transform->scalingLocal.scaling().z);

	json_serialize_to_file(file, "Config.json");

	for (GameObject* go : children)
	{
		go->SaveState(file);
	}
	return true;
}

bool GameObject::LoadState(JSON_Value* file)
{

	std::string name = this->name;
	const char* buf = name.c_str();

	mat4x4 translation = IdentityMatrix;

	translation.translate(json_object_dotget_number(json_object(file), std::string(name + " Position.x").c_str()), json_object_dotget_number(json_object(file), std::string(name + " Position.y").c_str()), json_object_dotget_number(json_object(file), std::string(name + " Position.z").c_str()));
	
	transform->transformLocal = translation;

	transform->ApplyTransformations();

	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.x", (double).x);
	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.y", (double)X.y);
	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.z", (double)X.z);

	mat4x4 scaling = IdentityMatrix;

	scaling.scale(json_object_dotget_number(json_object(file), "object.Scale.x"), json_object_dotget_number(json_object(file), "object.Scale.y"), json_object_dotget_number(json_object(file), "object.Scale.z"));

	transform->scalingLocal = scaling;

	App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));

	
	

	for (GameObject* go : children)
	{
		go->LoadState(file);
	}
	return true;
}


void GameObject::AddComponent(GOC_Type type)
{

	for (auto component : components)
	{
		if (component->GetGOC_Type() == type)
		{
			App->ui->AppendToOutput(DEBUG_LOG("There already exists a component of that type in %s!", name));
			return;
		}
		else
		{
			GameObjectComponent* comp = engineSystem->CreateNewGOC(this, type);
			components.push_back(comp);
			return;

		}
	}

}

GameObjectComponent* GameObject::GetComponent(GOC_Type type)
{
	for (auto component : components)
	{
		if (component->GetGOC_Type() == type)
		{
			
			return component;
		}
	}

	//App->ui->AppendToOutput(DEBUG_LOG("There is not any component of that type in %s!", name.c_str()));

}

GameObject* GameObject::CreateChildren()
{
	GameObject* go = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
	go->parent = this;
	children.push_back(go);

	return go;
}

void GameObject::CopyFromGameObject(GameObject gameobject)
{
	*this = gameobject;
}


void GameObject::AttachChild(GameObject* child)
{
	if (child->parent != nullptr)
		child->parent->RemoveChild(child);

	child->parent = this;
	children.push_back(child);
	//child->transform->NewAttachment();
	//child->PropagateTransform();
}

void GameObject::RemoveChild(GameObject* child)
{
	auto it = std::find(children.begin(), children.end(), child);
	if (it != children.end())
	{
		children.erase(it);
	}
}

void GameObject::Delete()
{
	//erase children
	for (GameObject* child : children)
	{
		child->Delete();
	}
	children.clear();



	for (GameObjectComponent* component : components)
	{
		std::vector<GameObjectComponent*>::iterator posGoc;
		for (GameObjectComponent* goc : App->engineSystem->GetAllGameObjectComponents())
		{
			if (goc->GetGameObject()->id == id)
			{
				App->engineSystem->GetAllGameObjectComponents().erase(posGoc);
			}
			posGoc++;
		}

		delete component;
	}
	components.clear();



	std::vector<GameObject*>::iterator pos;
	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
	{
		if (go->id == id)
		{
			App->engineSystem->GetCurrentScene()->gameObjects.erase(pos);
		}
		pos++;
	}

	std::vector<GameObject*>::iterator pos1;
	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
	{
		if (go->id == id)
		{
			App->engineSystem->GetAllGameObjects().erase(pos1);
		}
		pos++;
	}

}
