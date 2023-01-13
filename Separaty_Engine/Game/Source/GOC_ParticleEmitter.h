#pragma once
#include "GameObject.h"
#include "Globals.h"
#include <vector>

#include "CookieDevsParticles/ParticleSystem.h"

class Emitter;

class GOC_ParticleEmitter : public GameObjectComponent
{
public:
	GOC_ParticleEmitter(GameObject* gameObjectAttached, int id);
	~GOC_ParticleEmitter();

	bool Execute();

	std::shared_ptr<Emitter> emitter;

private:

};

