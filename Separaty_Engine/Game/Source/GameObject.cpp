#include "GameObject.h"
#include "Globals.h"
#include "Glew/include/glew.h"

#include <gl/GL.h>
#include <gl/GLU.h>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

bool GameObject::Init()
{
	glBindVertexArray(VAO);

	return true;
}

bool GameObject::Start()
{

	return true;
}

update_status GameObject::Update(float dt)
{


	return UPDATE_CONTINUE;
}

update_status GameObject::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

bool GameObject::CleanUp()
{

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