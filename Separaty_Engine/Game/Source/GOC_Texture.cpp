#include "GOC_Texture.h"


void GOC_Texture::UpdateMeshRendererTexture()
{
	GOC_MeshRenderer* renderer = nullptr;
	renderer = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	
	if (renderer != nullptr)
	{
		renderer->SetTexture(texture);
	}
}

void GOC_Texture::SetGoChildrenTexture(Texture* texture)
{
	for (GameObject* child : gameObject->GetChildren())
	{
		GOC_MeshRenderer* renderer = (GOC_MeshRenderer*)child->GetComponent(GOC_Type::GOC_MESH_RENDERER);
		renderer->SetTexture(texture);
	}
}
