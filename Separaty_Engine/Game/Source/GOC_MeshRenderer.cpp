#include "GOC_MeshRenderer.h"


GOC_MeshRenderer::GOC_MeshRenderer(GameObject* gameObjectAttached, mat4x4 transform)
{
	this->transform = transform;
	gameObject = gameObjectAttached;
	GOC_type = GOC_Type::GOC_MESH_RENDERER;
}

GOC_MeshRenderer::~GOC_MeshRenderer()
{
}

void GOC_MeshRenderer::SetMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
{

	//for (size_t i = 0; i < vertices.size(); i += 3)
	//{
	//	vertices[i] += transform.translation().x;
	//	vertices[i + 1] += transform.translation().y;
	//	vertices[i + 2] += transform.translation().z;
	//}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}




	// ..:: Initialization code :: ..
	// 1. bind Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void GOC_MeshRenderer::Render()
{
	glPushMatrix();
	glMultMatrixf(transform.M);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	RenderAxis();
}

void GOC_MeshRenderer::RenderAxis()
{

	// Draw Axis Grid
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

	glEnd();

	glLineWidth(1.0f);

	glPopMatrix();
}

bool GOC_MeshRenderer::Execute()
{
	//App->ui->AppendToOutput(DEBUG_LOG("executing"));
	transform = gameObject->transform->Get4x4Matrix();
	Render();

	return true;
}