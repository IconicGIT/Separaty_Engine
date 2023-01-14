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
#include <time.h>

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

	CDeVertex(float3 &v)
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

	CDeVertex operator += (const float3& v)
	{
		
		this->Position.x += v.x;
		this->Position.y += v.y;
		this->Position.z += v.z;

		return *this;
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
	void DrawParticle(int index);

	void AppendToDelete();
	void Delete();
	void CreateSubmodule();

	//update order: UpdateSubmodules() in preUpdate -> Update() self and spawns if necessary -> DrawParticles() on postUpdate

	std::vector<std::shared_ptr<Submodule>> submodules;
	std::vector< std::shared_ptr<Particle>> particles;
	bool pendingToDelete = false;

	float3 position;
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
	float particle_rate;
	bool  particle_rate_isRanged;
	float particle_rate_range[2];


	float timer;
	bool repeat = true;


	//particle parameters
	int   particle_amount;
	bool  particle_amount_isRanged;
	int particle_amount_range[2];

	float particle_lifetime;
	bool  particle_lifetime_isRanged;
	float particle_lifetime_range[2];

	float4 particle_color;

	float3 particle_originPosition;
	bool   particle_originPosition_isRanged;
	float3 particle_originPosition_range[2];

	float3  particle_velocity;
	bool   particle_velocity_isRanged;
	float3  particle_velocity_range[2];

	float3  particle_acceleration;
	bool   particle_acceleration_isRanged;
	float3  particle_acceleration_range[2];

	float3 particle_direction;
	bool   particle_direction_isRanged;
	float3 particle_direction_range[2];


	bool particle_followOrigin;

	
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
	Particle(Emitter* emitter);
	~Particle();

	void Update(float dt);
	void SetParticleMesh();
	void UpdateParticleMesh(float dt);
	
	void OnDeath();

	CDeVertex vertices[4];
	float3 quad_vertices[4];

	int indices[6];

	
	Emitter* emitter;
	std::vector<std::shared_ptr<Submodule>> submodules;

	//customizable parameters;

	float  lifetime = 0;
	float4 color;
	float3 originPosition;
	float3 localPosition;
	float3  velocity;
	float3  acceleration;
	float3 direction;
	bool   followOrigin;


private:

};

