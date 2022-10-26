#pragma once

#include "GameObject.h"
#include <vector>

#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glmath.h"

class GameObjectComponent;
class GameObject;
 
class GOC_MeshRenderer : public GameObjectComponent
{
public:
	GOC_MeshRenderer(GameObject* gameObjectAttached, mat4x4 transform);
	~GOC_MeshRenderer();


	void Render();
	bool Execute();

	void SetMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);

	void RenderAxis();

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

private:

	vec3 lightColor;
	vec3 toyColor;
	vec3 result;

};

