#pragma once
#include <iostream>

#include "..\Globals.h"
#include "..\Module.h"
#include "..\Application.h"
#include "..\ModuleUI.h"

#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "../glmath.h"


class Emitter;
class Submodule;
class Particle;

class CDeVertex {

public:
	CDeVertex() {}
	~CDeVertex(){}

	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;

	CDeVertex(vec3 v)
	{
		Position = v;
	}

	CDeVertex(vec v)
	{
		Position.x = v.x;
		Position.y = v.y;
		Position.z = v.z;
	}

	CDeVertex(int x, int y, int z)
	{
		Position.x = x;
		Position.y = y;
		Position.z = z;
	}

	CDeVertex operator + (const float3&v)
	{
		CDeVertex ret;
		ret.Position.x += v.x;
		ret.Position.y += v.y;
		ret.Position.z += v.z;

		return ret;
	}

};

class ParticleSystem : public Module
{
public:
	ParticleSystem();
	~ParticleSystem();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	std::vector<std::shared_ptr<Emitter>> allEmitters;

	std::shared_ptr<Emitter> CreateEmitter();
	
private:

};


/// <summary>
/// This element will exist as a world element.
/// An Emitter is controlled by the Particle System and is holder of one or multiple Submodules. If necessary they can be updated manually using the PreUpdate, Update and PostUpdate functions, in said order.
/// 
/// This element will update and draw the particles.
/// </summary>
class Emitter
{
public:
	Emitter();
	~Emitter();

	void PreUpdate(float dt);
	void Update(float dt);
	void PostUpdate(float dt);

	void UpdateSubmodules(float dt);
	void DrawParticles();

	void AppendToDelete();
	void Delete();
	void CreateSubmodule();

	//update order: UpdateSubmodules() in preUpdate -> Update() self and spawns if necessary -> DrawParticles() on postUpdate

	std::vector<std::shared_ptr<Submodule>> submodules;
	std::vector<std::shared_ptr<Particle>> particles;
	bool pendingToDelete = false;

private:
	unsigned int VAO, VBO, EBO;
};


/// <summary>
/// A Submodule is a component of the Emitter.It is controlled by their parent Emitter and is in charge of adding and customizing the particles the Emitter spawns.
/// </summary>
class Submodule
{
public:
	Submodule() {}
	Submodule(Emitter* emitter);
	~Submodule();

	void Update(float dt);
	void Execute();

	/// <summary>
	/// When needed, adds this Submodule's particles to the Emitter.
	/// </summary>
	void AddParticles();

	
	//Submodule parameters
	float timer_reference;
	float timer;
	bool repeat = true;


	//particle parameters
	int particle_amount = 1;
	int particle_lifetime;
	int test;

	
private:
	Emitter* emitter;
};


/// <summary>
/// This element will exist as a world element.
/// Is spawned, updated and drawn by an Emitter instance and can be customized by an Emitter's Submodule instance.
/// </summary>
class Particle
{
public:
	Particle();
	Particle(float lifetime);
	~Particle();

	void Update(float dt);
	void SetParticleMesh();
	void UpdateParticleMesh();
	
	void OnDeath();

	CDeVertex vertices[4];

	int indices[6];

	float lifetime = 0;
	std::vector<std::shared_ptr<Submodule>> submodules;

	//customizable parameters;

	float4 color;
	float3 position;
	float velocity;
	float acceleration;
	float3 direction;


private:

};

