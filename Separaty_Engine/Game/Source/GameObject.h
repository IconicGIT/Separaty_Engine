#pragma once
#include "Globals.h"
#include "Module.h"
#include <iostream>
#include "Application.h"
#include "GOC_MeshRenderer.h"


class GOC_MeshRenderer;

class GameObject : public Module
{
public:
	GameObject(bool start_enabled = true);
	~GameObject();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	bool selected;


	GOC_MeshRenderer* meshRenderer;

	/*mat4x4 transform;*/


	//void RenderAxis();

	//unsigned int VAO;
	//unsigned int VBO;
	//unsigned int EBO;

	//Mesh mesh;

	//unsigned int vertexShader;
	//const char* vertexShaderSource = "#version 330 core\n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"void main()\n"
	//	"{\n"
	//	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	//	"}\0";

	//unsigned int shaderProgram;
	//

private:
	uint id;
	GameObject* parent;
	std::vector<GameObject*> children;


	/*
	
	- id
	- parent
	- children* list
	- component* list
	
	*/
};

