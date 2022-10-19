#ifndef __GameObject_H__
#define __GameObject_H__

#include "Globals.h"
#include "Module.h"
#include <iostream>
#include "Application.h"

struct Mesh
{
	std::vector<float> vertices;
	std::vector<int> indices;
};

class GameObject : public Module
{
public:
	GameObject(bool start_enabled = true);
	~GameObject();

	virtual bool Init();
	virtual bool Start();
	virtual update_status Update(float dt) override;
	virtual update_status PostUpdate(float dt) override;
	virtual bool CleanUp();
	virtual bool LoadState(JSON_Value* file) override;
	virtual bool SaveState(JSON_Value* file) const override;

	/*bool ImportMesh();*/



	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	Mesh mesh;

	unsigned int vertexShader;
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	unsigned int shaderProgram;
	
	/*
	
	- id
	- parent
	- children* list
	- component* list
	
	*/
};

#endif
