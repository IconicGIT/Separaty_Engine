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

CDevShader::CDevShader(const char* vertexPath, const char* fragmentPath)
{
	Set(vertexPath, fragmentPath);
}

void CDevShader::Set(const char* vertexPath, const char* fragmentPath)

{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		//std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		App->ui->AppendToOutput(DEBUG_LOG("FILE_NOT_SUCCESFULLY_READ"));
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		App->ui->AppendToOutput(DEBUG_LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED"));
		App->ui->AppendToOutput(DEBUG_LOG("%s", infoLog));
	};

	// similiar for Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		App->ui->AppendToOutput(DEBUG_LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED"));
		App->ui->AppendToOutput(DEBUG_LOG("%s", infoLog));
	}

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		App->ui->AppendToOutput(DEBUG_LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED"));
		App->ui->AppendToOutput(DEBUG_LOG("%s", infoLog));
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void CDevShader::Use()
{
	glUseProgram(ID);
}


void CDevShader::Unuse()
{
	glUseProgram(0);
}


void CDevShader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}


void CDevShader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}


void CDevShader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


void CDevShader::SetMat4x4(const std::string& name, mat4x4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, &value);
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
	position = float3(0, 0, 0);
	std::shared_ptr<Submodule> newSubmodule = std::make_shared<Submodule>(this, submoduleLastID);
	submodules.push_back(newSubmodule);
	submoduleLastID++;
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
	//unsigned int ID = glCreateProgram();
	//glAttachShader(ID, vertices);
	//glAttachShader(ID, fragmentShader);
	//glLinkProgram(ID);

	//glUseProgram(particles[index]->myShader->ID);


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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	// Specify position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, Position));
	glEnableVertexAttribArray(0);

	// Specify normal data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, Normal));
	glEnableVertexAttribArray(1);

	// Specify texture coordinates data
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CDeVertex), (void*)offsetof(CDeVertex, TexCoords));
	glEnableVertexAttribArray(2);

	// Use the Shader program
	//particles[index]->myShader->Use();

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	if (!particles[index]->textures.empty())
	{
		for (unsigned int i = 0; i < particles[index]->textures.size(); i++)
		{
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = particles[index]->textures[i]->type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

				// Bind the texture to the corresponding texture unit
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, particles[index]->textures[i]->id);

			// Set the uniform variable for the texture in the fragment shader
			glUniform1i(glGetUniformLocation(particles[index]->myShader->ID, ("material." + name + number).c_str()), i);
		}
	}

	// Draw the mesh using the indices
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//particles[index]->myShader->Unuse();

	// Unbind the vertex array after drawing
	glBindVertexArray(0);

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

std::shared_ptr<Submodule> Emitter::CreateSubmodule()
{
	std::shared_ptr<Submodule> newSubmodule = std::make_shared<Submodule>(this, submoduleLastID);
	submodules.push_back(newSubmodule);
	submoduleLastID++;
	return newSubmodule;
}

std::shared_ptr<Submodule> Emitter::GetSubmodule(uint id)
{
	for (size_t i = 0; i < submodules.size(); i++)
	{
		if (submodules[i]->id == id)
		{
			return submodules[i];
		}
	}
	return nullptr;
}

		//Submodule
///////////////////////////////////////////

Submodule::Submodule(Emitter* emitter, uint id)
{
	this->emitter = emitter;
	this->id = id; 

	//Submodule settings
	particle_rate = 2;
	particle_rate_isRanged = false;
	particle_rate_range[0] = particle_rate;
	particle_rate_range[1] = particle_rate;

	timer = particle_rate;

	particle_texture_rowsColumnsToSet[0] = 1;
	particle_texture_rowsColumnsToSet[1] = 1;
	particle_texture_amountToSet = particle_texture_rowsColumnsToSet[0] * particle_texture_rowsColumnsToSet[1];

	particle_texture_rowsColumnsUsing[0] = 1;
	particle_texture_rowsColumnsUsing[1] = 1;
	particle_texture_amountUsing = particle_texture_rowsColumnsUsing[0] * particle_texture_rowsColumnsUsing[1];
	

	//initialize particle settings
	particle_mainShader = std::make_shared<CDevShader>("Assets/Project_1/Assets/Shaders/default.vertex", "Assets/Project_1/Assets/Shaders/default.fragment");
	particle_selectedShader = std::make_shared<CDevShader>("Assets/Project_1/Assets/Shaders/default.vertex", "Assets/Project_1/Assets/Shaders/selected.fragment");
	particle_textureReference = std::make_shared<CDevTexture>();

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

	particle_followEmitter = false;


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


		//here all particle properties will be set
		
		/*p->color = particle_color;*/

		p->myShader = particle_mainShader;
		p->selectedShader = particle_selectedShader;

		if (particle_lifetime_isRanged)
		{
			p->lifetime = RandomRange(particle_lifetime_range[0], particle_lifetime_range[1]);
		}
		else
		{
			p->lifetime = particle_lifetime;
		}


		if (particle_originPosition_isRanged)
		{
			float x = RandomRange(particle_originPosition_range[0].x, particle_originPosition_range[1].x);
			float y = RandomRange(particle_originPosition_range[0].y, particle_originPosition_range[1].y);
			float z = RandomRange(particle_originPosition_range[0].z, particle_originPosition_range[1].z);

			p->originPosition = float3(x, y, z);
		}
		else
		{
			p->originPosition = particle_originPosition;

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
		
		p->followEmitter = particle_followEmitter;

		p->textures = particle_textures;

		emitter->particles.push_back(p);
	}
}


void Submodule::SetTextureSliceData()
{
	particle_texture_rowsColumnsUsing[0] = particle_texture_rowsColumnsToSet[0];
	particle_texture_rowsColumnsUsing[1] = particle_texture_rowsColumnsToSet[1];
	particle_texture_amountUsing = particle_texture_amountToSet;
}


void Submodule::SetTexture(std::shared_ptr<CDevTexture> texture)
{
	this->particle_textureReference = texture;

	particle_textures.clear();
	particle_textures.push_back(particle_textureReference); 
}

void Submodule::SetTextures(std::vector<std::shared_ptr<CDevTexture>> textures)
{
	particle_textures.clear();
	particle_textures = textures;
}

void Submodule::FuncionChorra(std::shared_ptr<CDevTexture> a)
{
	DEBUG_LOG("ª");
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
	followEmitter = false;



	SetParticleMesh();
}

Particle::~Particle()
{
}

void Particle::Update(float dt)
{
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

	//vertex position
	quad_vertices[0] = float3(-1, 1, 0);			quad_vertices[3] = float3(1, 1, 0);


	quad_vertices[1] = float3(-1, -1, 0);		quad_vertices[2] = float3(1, -1, 0);
	
	for (size_t i = 0; i < 4; i++)
	{
		vertices[i] = CDeVertex(float3(quad_vertices[i]));
	}

	//vertex texture coordinates

	vertices[0].TexCoords = vec2(0, 1);		vertices[3].TexCoords = vec2(1, 1);


	vertices[1].TexCoords = vec2(0, 0);			vertices[2].TexCoords = vec2(1, 0);


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
		CDeVertex tmp = vertices[i];
		vertices[i] = quad_vertices[i] + originPosition + localPosition;

		if (followEmitter)
		{
			vertices[i] = quad_vertices[i] + emitter->position + originPosition + localPosition;
		}

		vertices[i].TexCoords = tmp.TexCoords;
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