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

private:

	Texture* texture;

};