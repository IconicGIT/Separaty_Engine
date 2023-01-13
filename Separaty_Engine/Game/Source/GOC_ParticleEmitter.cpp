#pragma once
#include "GOC_ParticleEmitter.h"
#include "Application.h"

GOC_ParticleEmitter::GOC_ParticleEmitter(GameObject* gameObjectAttached, int id)
{
	this->id = id;

	gameObject = gameObjectAttached;
	GOC_type = GOC_Type::GOC_PARTICLE_EMITTER;

	emitter = App->engineSystem->particleSystem->CreateEmitter();
}

GOC_ParticleEmitter::~GOC_ParticleEmitter()
{
}

bool GOC_ParticleEmitter::Execute()
{
	vec3 emitterPos = gameObject->transform->GetPosition();
	emitter->position = float3(emitterPos.x, emitterPos.y, emitterPos.z);
	return true;
}