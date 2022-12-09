#pragma once

#include "GameObject.h"
#include "Globals.h"
#include <vector>


#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glmath.h"

#include "Mesh.h"
#include "Model.h"
#include "Shader.h"






class GameObjectComponent;
class GameObject;
class Vertex;
class Model;
class Shader;
class Camera;


class GOC_MeshRenderer : public GameObjectComponent
{
public:
	GOC_MeshRenderer(GameObject* gameObjectAttached, mat4x4 transform, int id);
	~GOC_MeshRenderer();


	void Render();
	bool Execute();

	void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void SetMesh(Mesh* mesh);
	void SetTextures(std::vector<Texture> textures);
	void SetTextures(std::vector<Texture*> textures);
	void AddTextures(std::vector<Texture> textures);
	void AddTextures(std::vector<Texture*> textures);
	void AddTexture(Texture textures);

	void RenderAxis();

	Mesh GetMesh() const;

	GOC_Camera* goCamera;

	bool canDraw = true;

	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;
private:

	mat4x4 transform;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;


	unsigned int vertexShader;
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int shaderProgram;

	

	bool modelLoadSuccess = false;
	Shader* myShader;
	Shader *selctedShader;
	Mesh myMesh;

};

