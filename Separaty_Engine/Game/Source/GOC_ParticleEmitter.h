#pragma once
#include "GameObject.h"
#include "Globals.h"
#include <vector>

#include "CookieDevsParticles/ParticleSystem.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "MathGeoLib/Geometry/AABB.h"


class Emitter;
class Submodule;
class CDevTexture;
class CDevShader;

class GOC_ParticleEmitter : public GameObjectComponent
{
public:
	GOC_ParticleEmitter(GameObject* gameObjectAttached, int id);
	~GOC_ParticleEmitter();

	bool PreExecute(float dt);
	bool Execute(float dt);
	bool PostExecute(float dt);

	std::shared_ptr<Emitter> emitter;

	//void SetSubmoduleTexture(Texture texture, uint SubmoduleId);
	void SetSubmoduleTexture(std::shared_ptr<CDevTexture> submoduleTextureReference, std::shared_ptr<Submodule> &submodule);

	void DrawCube(static float3* corners, Color color);

	std::vector<AABB> submodulesAABB;

	void SetSubmoduleShader(std::shared_ptr<CDevShader> shader, std::shared_ptr<Submodule>& submodule);
	void SetSubmoduleShader(std::shared_ptr<CDevShader> shader, std::shared_ptr<Submodule>& submodule, mat4x4 projection, mat4x4 view);

private:

};

