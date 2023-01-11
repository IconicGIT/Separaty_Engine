#pragma once
#include "GOC_ParticleEmitter.h"


GOC_ParticleEmitter::GOC_ParticleEmitter(GameObject* gameObjectAttached, int id)
{
	this->id = id;

	gameObject = gameObjectAttached;
	GOC_type = GOC_Type::GOC_PARTICLE_EMITTER;
}

GOC_ParticleEmitter::~GOC_ParticleEmitter()
{
}

bool GOC_ParticleEmitter::Execute()
{
	return true;
}