#include "ParticleSystem.h"
#include "..\Log.h"

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
}

void Emitter::PostUpdate(float dt)
{
	if (!particles.empty())
	{
		DrawParticles();
	}
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

void Emitter::DrawParticles()
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

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CDeVertex), &vertices[0], GL_DYNAMIC_DRAW);

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

	glBindVertexArray(0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
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
	timer_reference = 2;
	timer = timer_reference;
	test = 0;

	//initialize particle settings
	particle_lifetime = 1;
}

Submodule::~Submodule()
{
}

void Submodule::Update(float dt)
{
	//App->ui->AppendToOutput(DEBUG_LOG("timer %f", timer));
	timer -= dt;
	test++;

	if (timer <= 0)
	{
		//DEBUG_LOG("Time!");
		test = 0;
		Execute();
		if (repeat) timer = timer_reference;
	}

}

void Submodule::Execute()
{
	AddParticles();
}

void Submodule::AddParticles()
{
	for (size_t i = 0; i < particle_amount; i++)
	{
		Particle* p = new Particle();


		//here all perticle properties will be set
		p->lifetime = particle_lifetime;

		emitter->particles.emplace_back(p);
	}
}


		//Particle
///////////////////////////////////////////

Particle::Particle()
{
	SetParticleMesh();
}

Particle::Particle(float lifetime)
{
	SetParticleMesh();

	this->lifetime = lifetime;
}

Particle::~Particle()
{
}

void Particle::Update(float dt)
{
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
	vertices[0] = CDeVertex(-1, 1, 0);		vertices[3] = CDeVertex(1, 1, 0);


	vertices[1] = CDeVertex(-1, -1, 0);		vertices[2] = CDeVertex(1, -1, 0);
	

	//1st triangle
	indices[0] = 0;		
	

	indices[1] = 1;		indices[2] = 2;



	//2nd triangle
	indices[3] = 0;		indices[5] = 3;


						indices[4] = 2;
	

}

void Particle::UpdateParticleMesh()
{

	//quad
	vertices[0] = CDeVertex(-1, 1, 0);		vertices[3] = CDeVertex(1, 1, 0);


	vertices[1] = CDeVertex(-1, -1, 0);		vertices[2] = CDeVertex(1, -1, 0);


}