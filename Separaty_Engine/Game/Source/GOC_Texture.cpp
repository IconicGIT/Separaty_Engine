#include "GOC_Texture.h"


void GOC_Texture::UpdateMeshRendererTexture(bool updateInGameObjectChildren)
{
	GOC_MeshRenderer* renderer = nullptr;
	renderer = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	
	if (renderer != nullptr)
	{
		renderer->SetTextures(textures);
	}

	if (updateInGameObjectChildren)
	{
		for (GameObject* child : gameObject->GetChildren())
		{
			GOC_MeshRenderer* renderer = nullptr;
			renderer = (GOC_MeshRenderer*)child->GetComponent(GOC_Type::GOC_MESH_RENDERER);
			renderer->SetTextures(textures);
		}
	}
}

bool GOC_Texture::LoadState(JSON_Value* file, std::string root)
{
	return true;
}

bool GOC_Texture::SaveState(JSON_Value* file, std::string root) const
{
	return true;
}