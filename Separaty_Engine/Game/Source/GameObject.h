#pragma once
#include "Globals.h"
#include "Module.h"
#include <iostream>
#include "Application.h"
#include "GameObjComponent.h"
#include "GOC_MeshRenderer.h"
#include "GOC_Transform.h"


class EngineSystem;
enum class GOC_Type;
//class GameObjectComponent;
class GOC_MeshRenderer;
class GOC_Transform;

struct PanelGameObjectInfo
{
	int selectedGameObjectID = -1;
};

class GameObject : public Module
{
public:
	GameObject(uint id, EngineSystem* system, bool start_enabled = true);
	~GameObject();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp(); 
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	uint GetID() const
	{
		return id;
	}

	std::vector<GameObject*> GetChildren() const
	{
		return children;
	}

	std::string GetName()
	{
		return name;
	}

	void AddComponent(GOC_Type type);
	GameObjectComponent* GetComponent(GOC_Type type);
	bool selected;

	void AttachChild(GameObject* child);
	void RemoveChild(GameObject* child);

	GOC_Transform* transform;
	PanelGameObjectInfo panelGameObjectInfo = {};
	uint id;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	std::string name;

private:
	EngineSystem* engineSystem;


	//This should not be here... but where???
	//double pointers??
	std::vector<GameObjectComponent*> components;

	//temp vars
	float a = 0;

};

