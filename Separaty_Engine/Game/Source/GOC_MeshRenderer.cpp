#include "GOC_MeshRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

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


	myShader.Set("Assets/Project_1/Assets/Shaders/default.vertex", "Assets/Project_1/Assets/Shaders/default.fragment");

	modelLoadSuccess = myModel.Set("Assets/Project_1/Assets/Models/baker_house.fbx");

	//int  success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}




	//// ..:: Initialization code :: ..
	//// 1. bind Vertex Array Object
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	//// 2. copy our vertices array in a vertex buffer for OpenGL to use
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	//// 3. copy our index array in a element buffer for OpenGL to use
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	//// 4. then set the vertex attributes pointers
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

}

void GOC_MeshRenderer::Render()
{
	/*glPushMatrix();
	glMultMatrixf(transform.M);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	if (modelLoadSuccess)
	{

		GOC_Transform* GoTransform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);

		myShader.Use();

		mat4x4 projection = perspective(DEGTORAD * App->camera->GetZoom(), (float)App->window->width / (float)App->window->height, 0.1f, 100.0f);
		mat4x4 view = App->camera->GetViewMatrix();
		myShader.SetMat4x4("projection", App->renderer3D->ProjectionMatrix);
		myShader.SetMat4x4("view", view);

		// render the loaded model
		mat4x4 model = IdentityMatrix;
		model.translate(gameObject->transform->GetPosition().x, gameObject->transform->GetPosition().y, gameObject->transform->GetPosition().z); // translate it down so it's at the center of the scene
		model.scale(gameObject->transform->GetScale().x, gameObject->transform->GetScale().y, gameObject->transform->GetScale().z);	// it's a bit too big for our scene, so scale it down

		myShader.SetMat4x4("model", model);

		myModel.Draw(myShader);
	}

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