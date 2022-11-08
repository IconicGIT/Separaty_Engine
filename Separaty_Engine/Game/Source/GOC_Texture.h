#pragma once
#include "GameObject.h"
#include "GameObjComponent.h"
#include "Model.h"
#include "Texture.h"

class GameObjectComponent;
class GameObject;
class GOC_MeshRenderer;
class Texture;

class GOC_Texture : public GameObjectComponent
{
public:
	GOC_Texture(GameObject* gameObjectAttached) 
	{
		GOC_type = GOC_Type::GOC_TEXTURE;
		gameObject = gameObjectAttached;
	}
	~GOC_Texture(){}

	bool Execute()
	{
		return true;
	}

	void SetTexture(Texture* texture)
	{
		this->texture = texture;
	}

	Texture* GetTexture() const
	{
		return texture;
	}

	void UpdateMeshRendererTexture();
	void SetGoChildrenTexture(Texture* texture);

private:

	Texture* texture;

};