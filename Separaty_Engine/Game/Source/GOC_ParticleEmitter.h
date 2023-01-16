#pragma once
#include "GameObject.h"
#include "Globals.h"
#include <vector>

#include "CookieDevsParticles/ParticleSystem.h"
#include "Texture.h"
#include "TextureLoader.h"


class Emitter;
class Submodule;
class CDevTexture;

class GOC_ParticleEmitter : public GameObjectComponent
{
public:
	GOC_ParticleEmitter(GameObject* gameObjectAttached, int id);
	~GOC_ParticleEmitter();

	bool Execute();

	std::shared_ptr<Emitter> emitter;

	//void SetSubmoduleTexture(Texture texture, uint SubmoduleId);
	void SetSubmoduleTexture(std::shared_ptr<CDevTexture> submoduleTextureReference, std::shared_ptr<Submodule> &submodule);

private:

};

