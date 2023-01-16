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
//
//void GOC_ParticleEmitter::SetSubmoduleTexture(Texture texture, uint SubmoduleId)
//{
//	std::shared_ptr<Submodule> submod = emitter->GetSubmodule(SubmoduleId);
//
//	if (submod != nullptr)
//	{
//		std::vector<Texture> texList = LoadSlicedTexture(texture.path, submod->particle_texture_rowsColumnsUsing[0], submod->particle_texture_rowsColumnsUsing[1], submod->particle_texture_amountUsing);
//		std::vector<std::shared_ptr<CDevTexture>> submodTexList;
//
//		for (Texture tex : texList)
//		{
//			std::shared_ptr<CDevTexture> toAdd = std::make_shared<CDevTexture>();
//			toAdd->height = tex.height;
//			toAdd->id = tex.id;
//			toAdd->name = tex.name;
//			toAdd->nrChannels = tex.nrChannels;
//			toAdd->path = tex.path;
//			toAdd->type = tex.type;
//			toAdd->width = tex.width;
//
//			submodTexList.push_back(toAdd);
//		}
//
//		submod->SetTextures(submodTexList);
//		
//	}
//}

void GOC_ParticleEmitter::SetSubmoduleTexture(std::shared_ptr<CDevTexture> texture, std::shared_ptr<Submodule> &submodule)
{
	std::shared_ptr<Submodule> submod = emitter->GetSubmodule(submodule->id);
	submod->particle_textures.clear();

	if (submod != nullptr)
	{
		std::vector<Texture> texList = LoadSlicedTexture(texture->path, submod->particle_texture_rowsColumnsUsing[0], submod->particle_texture_rowsColumnsUsing[1], submod->particle_texture_amountUsing);
		std::vector<std::shared_ptr<CDevTexture>> submodTexList;

		for (Texture tex : texList)
		{
			std::shared_ptr<CDevTexture> toAdd = std::make_shared<CDevTexture>();
			toAdd->height = tex.height;
			toAdd->id = tex.id;
			toAdd->name = tex.name;
			toAdd->nrChannels = tex.nrChannels;
			toAdd->path = tex.path;
			toAdd->type = tex.type;
			toAdd->width = tex.width;

			submod->particle_textures.push_back(toAdd);
		}
		

	}

}
