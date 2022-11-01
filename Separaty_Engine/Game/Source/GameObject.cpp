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

	std::vector<GLfloat> vertices = {
		1.0,	1.0,	1.0,
		0.0f,	1.0,	1.0,
		1.0,	1.0,	0.0f,
		0.0f,	1.0,	0.0f,
		1.0,	0.0f,	1.0,
		0.0f,	0.0f,	1.0,
		0.0f,	0.0f,	0.0f,
		1.0,	0.0f,	0.0f
	};

	std::vector<uint> indices = {  // note that we start from 0!
		3, 2, 6, 7, 4, 2, 0,
		3, 1, 6, 5, 4, 1, 0
	};

	GOC_MeshRenderer* meshRenderer =  (GOC_MeshRenderer*)GetComponent(GOC_Type::GOC_MESH_RENDERER);

	/*meshRenderer->SetMesh(vertices, indices);*/
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

	if (id == 0)
	{
		
	}

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
			components.push_back(engineSystem->CreateNewGOC(this, type));
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

	children.push_back(go);

	return go;
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

