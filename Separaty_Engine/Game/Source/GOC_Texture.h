#include "GameObject.h"
#include "GameObjComponent.h"
#include "Model.h"

class GameObjectComponent;
class GameObject;

class GOC_Texture : public GameObjectComponent
{
public:
	GOC_Texture() {}
	~GOC_Texture(){}

	void SetTexture(Texture* texture)
	{
		this->texture = texture;
	}

	Texture* GetTexture() const
	{
		return texture;
	}

	void UpdateMeshRendererTexture()
	{
		GOC_MeshRenderer* renderer = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
		renderer->SetTexture(texture);
	}

private:

	Texture* texture;

};