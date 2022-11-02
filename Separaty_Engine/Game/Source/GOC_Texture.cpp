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