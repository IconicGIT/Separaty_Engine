#pragma once
#include "Globals.h"
#include <iostream>
#include "GameObject.h"

class GameObject;

class GameObjectComponent
{
public:
	GameObjectComponent()
	{
		enabled = true;
	}

	~GameObjectComponent()
	{
	}

protected:
	uint id;
	std::string name;
	bool enabled;
	GameObject* gameobject;

public:

	virtual bool Execute()
	{
		return true;
	}

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

