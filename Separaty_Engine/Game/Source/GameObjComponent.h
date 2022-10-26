#pragma once
#include "Globals.h"
#include <iostream>
#include "GameObject.h"

class GameObject;
class GOC_MeshRenderer;
class GOC_Transform;

enum class GOC_Type
{
	GOC_NULL = -4,
	GOC_TRANSFORM = 0,
	GOC_MESH_RENDERER = 1,
};



class GameObjectComponent
{
public:
	GameObjectComponent()
	{
		enabled = true;
		GOC_type = GOC_Type::GOC_NULL;
	}

	~GameObjectComponent()
	{
	}

protected:
	uint id;
	std::string name;
	bool enabled;
	GameObject* gameObject;
	GOC_Type GOC_type;
public:

	GOC_Type GetGOC_Type() const
	{
		return GOC_type;
	}

	virtual bool Execute() = 0;

	std::string GetName() const
	{
		return name;
	}

	bool IsEnabled() const
	{
		return enabled;
	}

	bool Enable()
	{
		enabled = true;
		return enabled;
	}

	bool Disable()
	{
		enabled = false;
		return enabled;
	}

};
