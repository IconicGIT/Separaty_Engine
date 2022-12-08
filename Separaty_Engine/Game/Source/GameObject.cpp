#include "GameObject.h"
#include "ModuleInput.h"

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
	AddComponent(GOC_Type::GOC_TRANSFORM);
	transform = (GOC_Transform*)components[0];
	return true;
}

bool GameObject::Start()
{
	AddComponent(GOC_Type::GOC_MESH_RENDERER);
	AddComponent(GOC_Type::GOC_TEXTURE);



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
	/*
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		App->ui->AppendToOutput(DEBUG_LOG("%s", name.c_str()));

		for (GameObjectComponent* comp : components)
		{
			App->ui->AppendToOutput(DEBUG_LOG("    %i", comp->GetID()));

		}

		App->ui->AppendToOutput(DEBUG_LOG("Engine components: %i", App->engineSystem->GetAllGameObjectComponents().size()));
	}*/

	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate(float dt)
{

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

void GameObject::Delete()
{
	//delete children
	for (GameObject* child : children)
	{
		child->Delete();
	}

	//delete components associated with gameobject
	App->engineSystem->EraseGameObjectComponentFromGameObject(this);


	//delete self from engineSystem and scene
	App->engineSystem->EraseGameObjectFromScenes(this);
	App->engineSystem->EraseGameObjectFromEngine(this);

	//call clean
	CleanUp();
	//delete self;
	delete this;

}



bool GameObject::SaveState(JSON_Value* file, std::string root) const
{
	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), std::string(root + name + " info.name").c_str(), std::string(name).c_str());


	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.position.x").c_str(), (double)transform->translationLocal.translation().x);
	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.position.y").c_str(), (double)transform->translationLocal.translation().y);
	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.position.z").c_str(), (double)transform->translationLocal.translation().z);

	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.x", (double).x);
	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.y", (double)X.y);
	//json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.z", (double)X.z);

	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.rotationRad.x").c_str(), (double)transform->rotationEulerLocal.x);
	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.rotationRad.y").c_str(), (double)transform->rotationEulerLocal.y);
	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.rotationRad.z").c_str(), (double)transform->rotationEulerLocal.z);


	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.scale.x").c_str(), (double)transform->scalingLocal.scaling().x);
	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.scale.y").c_str(), (double)transform->scalingLocal.scaling().y);
	json_object_dotset_number(json_object(file), std::string(root + name + " info.transform.scale.z").c_str(), (double)transform->scalingLocal.scaling().z);

	json_serialize_to_file(file, "Config.json");

	for (GameObject* go : children)
	{
		go->SaveState(file);
	}
	return true;
}

bool GameObject::LoadState(JSON_Value* file, std::string root)
{


	/*const char* n = json_object_dotget_string(json_object(file), "gameObjects");*/

	std::string name = this->name;
	const char* buf = name.c_str();

	name = json_object_dotget_string(json_object(file), std::string(root + name + " info.name").c_str());

	//load position
	mat4x4 translation = IdentityMatrix;

	vec3 newPos = vec3(
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.position.x").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.position.y").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.position.z").c_str())
		);


	translation.translate(newPos.x, newPos.y, newPos.z);

	transform->translationLocal = translation;

	//Load rotation

	vec3 rotRad = vec3(
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.rotationRad.x").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.rotationRad.y").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.rotationRad.z").c_str())
	);
	
	Quat rotatorQuat = Quat::FromEulerXYZ(rotRad.x, rotRad.y, rotRad.z);
	aiQuaternion rotationQuat(rotatorQuat.w, rotatorQuat.x, rotatorQuat.y, rotatorQuat.z);


	aiMatrix3x3* tempMat3 = new aiMatrix3x3;

	aiQuaternion* tempRotationQuat = new aiQuaternion(rotationQuat);

	//aiMatrix4FromScalingQuaternionPosition(tempMat, tempScale, tempRotationQuat, tempPosition);
	aiMatrix3FromQuaternion(tempMat3, tempRotationQuat);

	mat4x4 resMat = IdentityMatrix;

	resMat[0] = (float)tempMat3->a1;
	resMat[1] = (float)tempMat3->a2;
	resMat[2] = (float)tempMat3->a3;
	resMat[3] = 0;

	resMat[4] = (float)tempMat3->b1;
	resMat[5] = (float)tempMat3->b2;
	resMat[6] = (float)tempMat3->b3;
	resMat[7] = 0;

	resMat[8] = (float)tempMat3->c1;
	resMat[9] = (float)tempMat3->c2;
	resMat[10] = (float)tempMat3->c3;
	resMat[11] = 0;

	resMat[12] = 0;
	resMat[13] = 0;
	resMat[14] = 0;
	resMat[15] = 1;

	resMat.transpose();

	transform->rotationLocal = resMat;
	transform->rotationEulerLocal = float3(rotRad.x, rotRad.y, rotRad.z);


	//load scaling
	mat4x4 scaling = IdentityMatrix;

	vec3 newScale = vec3(
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.scale.x").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.scale.y").c_str()),
		json_object_dotget_number(json_object(file), std::string(root + name + " info.transform.scale.z").c_str())
	);

	scaling.scale(newScale.x, newScale.y, newScale.z);

	transform->scalingLocal = scaling;



	transform->ApplyTransformations();

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
			App->ui->AppendToOutput(DEBUG_LOG("There already exists a component of that type in %s!", name.c_str()));
			return;
		}
	}
	GameObjectComponent* comp = engineSystem->CreateNewGOC(this, type);
	components.push_back(comp);

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

//void GameObject::Delete()
//{
//	//erase children
//	for (GameObject* child : children)
//	{
//		child->Delete();
//	}
//	children.clear();
//
//
//
//	for (GameObjectComponent* component : components)
//	{
//		std::vector<GameObjectComponent*>::iterator posGoc;
//		for (GameObjectComponent* goc : App->engineSystem->GetAllGameObjectComponents())
//		{
//			if (goc->GetGameObject()->id == id)
//			{
//				App->engineSystem->GetAllGameObjectComponents().erase(posGoc);
//			}
//			posGoc++;
//		}
//
//		delete component;
//	}
//	components.clear();
//
//
//
//	std::vector<GameObject*>::iterator pos;
//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
//	{
//		if (go->id == id)
//		{
//			App->engineSystem->GetCurrentScene()->gameObjects.erase(pos);
//		}
//		pos++;
//	}
//
//	std::vector<GameObject*>::iterator pos1;
//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
//	{
//		if (go->id == id)
//		{
//			App->engineSystem->GetAllGameObjects().erase(pos1);
//		}
//		pos++;
//	}
//
//}
