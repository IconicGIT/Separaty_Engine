#include "GameObject.h"
#include "Globals.h"
#include <vector>


class GOC_ParticleEmitter : public GameObjectComponent
{
public:
	GOC_ParticleEmitter(GameObject* gameObjectAttached, int id);
	~GOC_ParticleEmitter();

	bool Execute();

private:

};

