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
#include <list>

#include "SDL/include/SDL_rect.h"

#define MAX_FRAMES 60

class Emitter;
class Submodule;
class Particle;

class CDevShader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
	CDevShader(){}
	CDevShader(const char* vertexPath, const char* fragmentPath);
    void Set(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void Use();
    void Unuse();

    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;

    void SetMat4x4(const std::string& name, mat4x4 value) const;

	mat4x4 proj, view, model;
};


struct CDevTexture {
	std::string name;
	unsigned int id;
	std::string type;
	std::string path;

	int width;
	int height;
	int nrChannels;
};

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

struct ColorTime
{
	float4 color = float4::one;
	float position = 0.0f;
	std::string name = " ";
	//open window for change particle color
	bool changingColor = false;

	bool operator<(const ColorTime& color) const
	{
		return position < color.position;
	}
};


class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	bool loop = true;
	// Allows the animation to keep going back and forth
	bool pingpong = false;
	bool mustFlip = false;

private:
	float currentFrame = 0.0f;
	int totalFrames = 0;
	int loopCount = 0;
	int pingpongDirection = 1;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void Reset()
	{
		currentFrame = 0;
		loopCount = 0;
	}

	bool HasFinished()
	{
		return !loop && !pingpong && loopCount > 0;
	}

	void Update()
	{
		currentFrame += speed;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop || pingpong) ? 0.0f : totalFrames - 1;
			++loopCount;

			if (pingpong)
				pingpongDirection = -pingpongDirection;
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		int actualFrame = currentFrame;
		if (pingpongDirection == -1)
			actualFrame = totalFrames - currentFrame;

		return frames[actualFrame];
	}
};


// //////////////////////////////////

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
	std::vector<std::shared_ptr<CDevTexture>> allTextures;

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
	void UpdateSubmoduleShaderData(std::shared_ptr<Submodule>& submodule, mat4x4 projection, mat4x4 view);

	void AppendToDelete();
	void Delete();
	std::shared_ptr<Submodule> CreateSubmodule();
	std::shared_ptr<Submodule> GetSubmodule(uint id);
	

	bool EditColor(ColorTime& colorTime, uint pos = 0u);

	ImVec4 EqualsFloat4(const float4 float4D);

	//update order: UpdateSubmodules() in preUpdate -> Update() self and spawns if necessary -> DrawParticles() on postUpdate

	std::vector<std::shared_ptr<Submodule>> submodules;
	std::vector< std::shared_ptr<Particle>> particles;
	bool pendingToDelete = false;
	uint submoduleLastID = 0;

	float3 position;
	mat4x4 transformLocal;
	mat4x4 transformWorld;

	mat4x4 translationLocal;
	mat4x4 translationWorld;

	mat4x4 scalingLocal;
	mat4x4 scalingWorld;

	mat4x4 rotationLocal;
	mat4x4 rotationWorld;

	bool timeColor = false;
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
	Submodule(Emitter* emitter, uint id);
	~Submodule();

	void Update(float dt);
	void Execute();

	/// <summary>
	/// When needed, adds this Submodule's particles to the Emitter.
	/// </summary>
	void AddParticles();
	void SetTextureSliceData();
	void SetTexture(std::shared_ptr<CDevTexture> texture);
	void SetTextures(std::vector<std::shared_ptr<CDevTexture>> textures);
	void FuncionChorra(std::shared_ptr<CDevTexture> a);

	//Submodule data
	uint id;
	std::shared_ptr<CDevShader> particle_mainShader;
	std::shared_ptr<CDevShader> particle_selectedShader;

	std::shared_ptr<CDevTexture> particle_textureReference;
	std::vector<std::shared_ptr<CDevTexture>> particle_textures;
	
	float timer;


	//Submodule parameters
	float particle_rate;
	bool  particle_rate_isRanged;
	float particle_rate_range[2];

	bool repeat = true;

	bool particle_texture_isSliced = false;
	int particle_texture_rowsColumnsToSet[2];
	int particle_texture_rowsColumnsUsing[2];
	int particle_texture_amountToSet;
	int particle_texture_amountUsing;


	//particle parameters

	

	int   particle_amount;
	bool  particle_amount_isRanged;
	int   particle_amount_range[2];

	float particle_lifetime;
	bool  particle_lifetime_isRanged;
	float particle_lifetime_range[2];

	std::list<ColorTime> particle_color;
	
	int nextPos = 100;
	float4 nextColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

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

	bool particle_followEmitter;


	Emitter* emitter;
private:
	
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

	//particle mesh
	CDeVertex vertices[4];
	float3 quad_vertices[4];
	int indices[6];

	mat4x4 transformLocal;
	mat4x4 transformWorld;

	mat4x4 translationLocal;
	mat4x4 translationWorld;

	mat4x4 scalingLocal;
	mat4x4 scalingWorld;

	mat4x4 rotationLocal;
	mat4x4 rotationWorld;

	//particle data
	Emitter* emitter;
	std::vector<std::shared_ptr<Submodule>> submodules;
	std::vector<std::shared_ptr<CDevTexture>> textures;
	std::shared_ptr<CDevShader> myShader;
	std::shared_ptr<CDevShader> selectedShader;
	

	//customizable parameters;
	float  lifetime = 0;
	float4 color;
	float3 originPosition;
	float3 localPosition;
	float3  velocity;
	float3  acceleration;
	float3 direction;
	bool   followEmitter;


private:

};

