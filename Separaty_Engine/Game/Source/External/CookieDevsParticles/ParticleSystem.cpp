#include "ParticleSystem.h"
#include "..\Log.h"

float RandomRange(float value01, float value02) {

	if (value01 > value02) {

		float i = value01;
		value01 = value02;
		value02 = i;

	}

	float ret = value01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (value02 - value01)));

	return ret;

}


		//Particle System
///////////////////////////////////////////

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::Init()
{
	srand(time(0));
	return true;
}

bool ParticleSystem::Start()
{
	return true;

}

update_status ParticleSystem::PreUpdate(float dt)
{
	for (size_t i = 0; i < allEmitters.size(); i++)
	{
		allEmitters[i]->PreUpdate(dt);
	}
	return UPDATE_CONTINUE;
}

update_status ParticleSystem::Update(float dt)
{
	//App->ui->AppendToOutput(DEBUG_LOG("particle engine"));
	for (size_t i = 0; i < allEmitters.size(); i++)
	{
		if (allEmitters[i]->pendingToDelete)
		{
			allEmitters[i]->Delete();
			allEmitters.erase(allEmitters.begin() + i);
		}

		allEmitters[i]->Update(dt);
	}

	//if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	//{
	//	DEBUG_LOG("rnd: %f", RandomRange(45.2f, 45.2f));
	//}

	return UPDATE_CONTINUE;
}

update_status ParticleSystem::PostUpdate(float dt)
{
	for (size_t i = 0; i < allEmitters.size(); i++)
	{
		allEmitters[i]->PostUpdate(dt);
	}
	return UPDATE_CONTINUE;
}

bool ParticleSystem::CleanUp()
{
	for (size_t i = 0; i < allEmitters.size(); i++)
	{	
		allEmitters[i]->Delete();
		allEmitters.erase(allEmitters.begin() + i);
	}
	allEmitters.clear();
	return true;

;
}


std::shared_ptr<Emitter> ParticleSystem::CreateEmitter()
{
	std::shared_ptr<Emitter> newEmitter = std::make_shared<Emitter>();

	allEmitters.push_back(newEmitter);



	return newEmitter;
}

bool ParticleSystem::LoadState(JSON_Value* file, std::string root)
{
	return true;

}

bool ParticleSystem::SaveState(JSON_Value* file, std::string root) const
{
	return true;

}


		//Emitter
///////////////////////////////////////////

Emitter::Emitter()
{
	std::shared_ptr<Submodule> newSubmodule = std::make_shared<Submodule>(this);

	submodules.push_back(newSubmodule);
	position = float3(0, 0, 0);
}

Emitter::~Emitter()
{
}

void Emitter::PreUpdate(float dt)
{
	UpdateSubmodules(dt); 
}

void Emitter::Update(float dt)
{
	//App->ui->AppendToOutput(DEBUG_LOG("emitter"));
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->lifetime < 0)
		{
			particles[i]->OnDeath();
			particles.erase(particles.begin() + i);

			continue;
		}

		particles[i]->Update(dt);
	}

	if (!particles.empty())
	{
		for (size_t i = 0; i < particles.size(); i++)
		{
			DrawParticle(i);

		}
	}
}

void Emitter::PostUpdate(float dt)
{
	
}

void Emitter::UpdateSubmodules(float dt)
{
	for (size_t i = 0; i < submodules.size(); i++)
	{

		submodules[i]->Update(dt);

		if (submodules[i]->timer < 0)
		{
			submodules.erase(submodules.begin() + i);
		}

	}
}

void Emitter::DrawParticle(int index)
{
	/*
	{
	
		std::vector<CDeVertex> vertices;
		for (size_t i = 0; i < particles.size(); i++)
		{

			vertices.push_back(particles[i]->vertices[0]);
			vertices.push_back(particles[i]->vertices[1]);
			vertices.push_back(particles[i]->vertices[2]);
			vertices.push_back(particles[i]->vertices[3]);
		}

		std::vector<int> indices;
		for (size_t i = 0; i < particles.size(); i++)
		{
			indices.push_back(particles[i]->indices[0]);
			indices.push_back(particles[i]->indices[1]);
			indices.push_back(particles[i]->indices[2]);
			indices.push_back(particles[i]->indices[3]);
			indices.push_back(particles[i]->indices[4]);
			indices.push_back(particles[i]->indices[5]);
		}


		//set mesh
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CDeVertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, TexCoords));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

	*/

	
	CDeVertex vertices[4] = {
		particles[index]->vertices[0],
		particles[index]->vertices[1],
		particles[index]->vertices[2],
		particles[index]->vertices[3]
	};

	int indices[6] =
	{
		particles[index]->indices[0],
		particles[index]->indices[1],
		particles[index]->indices[2],
		particles[index]->indices[3],
		particles[index]->indices[4],
		particles[index]->indices[5]
	};

	//set mesh
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(CDeVertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, TexCoords));


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(4, &VAO);
	glDeleteBuffers(sizeof(VBO), &VBO);
	glDeleteBuffers(sizeof(EBO), &EBO);

}

/// <summary>
	/// This function is used internally to send Emitters to the deletion pipeline. Use this instead of Delete() to avoid problems.
	/// </summary>
void Emitter::AppendToDelete()
{
	pendingToDelete = true;
}


/// <summary>
/// This function is used internally to directly delete Emitters. Use AppendToDelete() instead to avoid problems.
/// </summary>
void Emitter::Delete()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->submodules.clear();
	}
	particles.clear();
}

void Emitter::CreateSubmodule()
{
	std::shared_ptr<Submodule> newSubmodule = std::make_shared<Submodule>(this);
	submodules.push_back(newSubmodule);
}

		//Submodule
///////////////////////////////////////////

Submodule::Submodule(Emitter* emitter)
{
	this->emitter = emitter;

	//Submodule settings
	particle_rate = 2;
	particle_rate_isRanged = false;
	particle_rate_range[0] = particle_rate;
	particle_rate_range[1] = particle_rate;

	timer = particle_rate;
	

	//initialize particle settings

	particle_amount = 1;
	particle_amount_isRanged = false;
	particle_amount_range[0] = particle_amount;
	particle_amount_range[1] = particle_amount;

	particle_lifetime = 1;
	particle_lifetime_isRanged = false;
	particle_lifetime_range[0] = particle_lifetime;
	particle_lifetime_range[1] = particle_lifetime;

	/*particle_color = float4(1,1,1,1)*/;

	particle_originPosition = float3(emitter->position.x, emitter->position.y, emitter->position.z);
	particle_originPosition_isRanged = false;
	particle_originPosition_range[0] = particle_originPosition;
	particle_originPosition_range[1] = particle_originPosition;

	particle_velocity = float3(0, 1, 0);
	particle_acceleration_isRanged = false;
	particle_velocity_range[0] = particle_velocity;
	particle_velocity_range[1] = particle_velocity;

	particle_acceleration = float3(0, 0, 0);
	particle_acceleration_isRanged = false;
	particle_acceleration_range[0] = particle_acceleration;
	particle_acceleration_range[1] = particle_acceleration;

	particle_direction = float3(0, 1, 0);
	particle_direction_isRanged = false;
	particle_direction_range[0] = particle_direction;
	particle_direction_range[1] = particle_direction;

	particle_followOrigin = false;


}

Submodule::~Submodule()
{
}

void Submodule::Update(float dt)
{
	//App->ui->AppendToOutput(DEBUG_LOG("timer %f", timer));
	timer -= dt;

	if (timer <= 0)
	{
		//DEBUG_LOG("Time!");
		Execute();
		if (repeat)
		{
			if (particle_rate_isRanged)
			{
				timer = RandomRange(particle_rate_range[0], particle_rate_range[1]);
			}
			else
			{
				timer = particle_rate;
			}
		}
	}

}

void Submodule::Execute()
{
	AddParticles();
}

void Submodule::AddParticles()
{

	int amountToAdd = particle_amount;

	if (particle_amount_isRanged)
	{
		amountToAdd = (int)RandomRange(particle_amount_range[0], particle_amount_range[1]);
	}


	for (size_t i = 0; i < amountToAdd; i++)
	{
		std::shared_ptr <Particle> p = std::make_shared<Particle>(emitter);


		//here all perticle properties will be set
		
		/*p->color = particle_color;*/

		if (particle_originPosition_isRanged)
		{
			float x = RandomRange(particle_originPosition_range[0].x, particle_originPosition_range[1].x);
			float y = RandomRange(particle_originPosition_range[0].y, particle_originPosition_range[1].y);
			float z = RandomRange(particle_originPosition_range[0].z, particle_originPosition_range[1].z);

			p->originPosition = float3(x, y, z);
		}
		else
		{
			p->originPosition = float3(emitter->position.x, emitter->position.y, emitter->position.z);

		}

		if (particle_velocity_isRanged)
		{
			
			float x = RandomRange(particle_velocity_range[0].x,particle_velocity_range[1].x);
			float y = RandomRange(particle_velocity_range[0].y,particle_velocity_range[1].y);
			float z = RandomRange(particle_velocity_range[0].z,particle_velocity_range[1].z);

			p->velocity = float3(x, y, z);
		}
		else
		{
			p->velocity = particle_velocity;
		}
		
		if (particle_acceleration_isRanged)
		{

			float x = RandomRange(particle_acceleration_range[0].x, particle_acceleration_range[1].x);
			float y = RandomRange(particle_acceleration_range[0].y, particle_acceleration_range[1].y);
			float z = RandomRange(particle_acceleration_range[0].z, particle_acceleration_range[1].z);

			p->acceleration = float3(x, y, z);
		}
		else
		{
			p->acceleration = particle_acceleration;
		}

		if (particle_direction_isRanged)
		{
			float x = RandomRange(particle_direction_range[0].x, particle_direction_range[1].x);
			float y = RandomRange(particle_direction_range[0].y, particle_direction_range[1].y);
			float z = RandomRange(particle_direction_range[0].z, particle_direction_range[1].z);

			p->direction = float3(x, y, z);
		}
		else
		{
			p->direction = particle_direction;
		}
		
		p->followOrigin = particle_followOrigin;

		emitter->particles.push_back(p);
	}
}


		//Particle
///////////////////////////////////////////

Particle::Particle()
{
	SetParticleMesh();
}

Particle::Particle(Emitter* emitter)
{
	this->emitter = emitter;

	
	//default settings upon creation. Deleted upon set by a Submodule
	lifetime = 1;
	color = float4(1, 1, 1, 1);
	originPosition = float3(emitter->position.x, emitter->position.y, emitter->position.z);
	localPosition = float3(0, 0, 0);
	velocity = float3(0, 0, 0);
	acceleration = float3(0, 0, 0);
	direction = float3(0, 0, 0);
	followOrigin = false;



	SetParticleMesh();
}

Particle::~Particle()
{
}

void Particle::Update(float dt)
{
	originPosition = emitter->position;
	UpdateParticleMesh(dt);
	if (lifetime > 0)
	{
		lifetime -= dt;
	}
}

void Particle::OnDeath()
{
	//App->ui->AppendToOutput(DEBUG_LOG("particle deleted"));
}

void Particle::SetParticleMesh()
{

	//quad
	quad_vertices[0] = float3(-1, 1, 0);			quad_vertices[3] = float3(1, 1, 0);


	quad_vertices[1] = float3(-1, -1, 0);		quad_vertices[2] = float3(1, -1, 0);
	
	for (size_t i = 0; i < 4; i++)
	{
		vertices[i] = CDeVertex(float3(quad_vertices[i]));
	}

	{
		//1st triangle
		indices[0] = 0;


		indices[1] = 1;		indices[2] = 2;



		//2nd triangle
		indices[3] = 0;		indices[5] = 3;


		indices[4] = 2;
	}
	
	
	for (size_t i = 0; i < 4; i++)
	{
		
		vertices[i] += originPosition;
		
	}

}

void Particle::UpdateParticleMesh(float dt)
{
	velocity += acceleration * dt;

	float3 resultantPosition = velocity * dt;

	/*float3 resultantVector = vec(direction).Normalized() * resultantPosition;*/

	localPosition += resultantPosition;


	for (size_t i = 0; i < 4; i++)
	{
		vertices[i] = quad_vertices[i] + localPosition;

		if (followOrigin)
		{
			vertices[i] = quad_vertices[i] + originPosition;
		}
	}
	
	

}

bool Emitter::EditColor(ColorTime& colorTime, uint pos)
{
	bool ret = true;
	ImVec4 color = EqualsFloat4(colorTime.color);
	if (ImGui::ColorButton(colorTime.name.data(), color, ImGuiColorEditFlags_None, ImVec2(100, 20)))
		colorTime.changingColor = !colorTime.changingColor;

	if (!colorTime.changingColor)
	{
		ImGui::SameLine();
		ImGui::TextUnformatted(colorTime.name.data());
		if (pos > 0)
		{
			std::string colorStr = "Remove Color ";
			colorStr.append(std::to_string(pos));
			ImGui::SameLine();
			if (ImGui::Button(colorStr.data(), ImVec2(125, 25)))
				ret = false;
		}
		else if (!timeColor)
			ret = false;
	}
	else
		ImGui::ColorEdit4(colorTime.name.data(), &colorTime.color.x, ImGuiColorEditFlags_AlphaBar);
	return ret;
}

ImVec4 Emitter::EqualsFloat4(const float4 float4D)
{
	ImVec4 vec;
	vec.x = float4D.x;
	vec.y = float4D.y;
	vec.z = float4D.z;
	vec.w = float4D.w;
	return vec;
}