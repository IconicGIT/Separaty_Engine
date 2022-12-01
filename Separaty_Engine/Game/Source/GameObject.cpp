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


bool GameObject::LoadState(JSON_Value* file)
{

	return true;
}

bool GameObject::SaveState(JSON_Value* file) const
{

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

	App->ui->AppendToOutput(DEBUG_LOG("There is not any component of that type in %s!", name));

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
