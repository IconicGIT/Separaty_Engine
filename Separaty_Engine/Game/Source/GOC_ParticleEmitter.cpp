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

	for (std::shared_ptr<Submodule> submod : emitter->submodules)
	{
		float3 arrayAABB[2] = { submod->particle_originPosition_range[0], submod->particle_originPosition_range[1] };

		AABB box;

		box.SetNegativeInfinity();

		box.Enclose(arrayAABB, 2);

		float3 arrayVec[8];

		for (size_t i = 0; i < 2; i++)
		{
			if (submod->particle_followEmitter)
			{
				arrayAABB[0] += float3(emitterPos.x, emitterPos.y, emitterPos.z);

				arrayAABB[1] += float3(emitterPos.x, emitterPos.y, emitterPos.z);
			}
			
		}

		box.GetCornerPoints(arrayVec);

		DrawCube(arrayVec, Color(1, 1, 1, 1));
	}


	return true;
}

void GOC_ParticleEmitter::DrawCube(static float3* corners, Color color)
{
	glLineWidth(2.0f);
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_QUADS);

	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[3]);
						
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);
	glVertex3fv((GLfloat*)&corners[6]);
						
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[7]);
						
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[2]);
						
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[2]);
						
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[1]);

	glEnd();

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
