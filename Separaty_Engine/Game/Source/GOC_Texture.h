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
		this->textures.clear();
		this->textures.push_back(texture);
	}

	void SetTexture(Texture texture)
	{
		if (!textures.empty()) this->textures.clear();
		Texture* t = new Texture(texture);
		textures.push_back(t);
	}

	void SetTextures(std::vector<Texture*> textures)
	{
		this->textures.clear();
		this->textures = textures;
	}

	void SetTextures(std::vector<Texture> textures)
	{
		std::vector<Texture*> textures_;

		for (Texture tex : textures)
		{
			Texture* t = new Texture(tex);
			textures_.push_back(t);
		}

		SetTextures(textures_);
		
	}

	void AddTexture(Texture texture)
	{
		textures.push_back(new Texture(texture));
	}

	std::vector<Texture*> GetTextures() const
	{
		return textures;
	}

	void UpdateMeshRendererTexture(bool updateInGameObjectChildren = false);

private:

	std::vector<Texture*> textures;

};