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
class Mesh;
class Model;
class Shader;


class GOC_MeshRenderer : public GameObjectComponent
{
public:
	GOC_MeshRenderer(GameObject* gameObjectAttached, mat4x4 transform);
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

	Mesh GetMesh() const
	{
		return  myMesh;
	}

private:

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;


	unsigned int vertexShader;

	unsigned int shaderProgram;

	

	bool modelLoadSuccess = false;
	Shader* myShader;
	Shader *selctedShader;
	Mesh myMesh;
};

