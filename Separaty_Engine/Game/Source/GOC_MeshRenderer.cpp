#include "GOC_MeshRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

GOC_MeshRenderer::GOC_MeshRenderer(GameObject* gameObjectAttached, mat4x4 transform, int id)
{
	this->id = id;

	this->transform = transform;
	gameObject = gameObjectAttached;
	GOC_type = GOC_Type::GOC_MESH_RENDERER;

	myShader = new Shader("Assets/Project_1/Assets/Shaders/default.vertex", "Assets/Project_1/Assets/Shaders/default.fragment");
	selctedShader = new Shader("Assets/Project_1/Assets/Shaders/default.vertex", "Assets/Project_1/Assets/Shaders/selected.fragment");

	
	

}

GOC_MeshRenderer::~GOC_MeshRenderer()
{
}

void GOC_MeshRenderer::SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	myMesh.vertices = vertices;
	myMesh.indices = indices;

	//myMesh.renderer = this;

}

void GOC_MeshRenderer::SetMesh(Mesh* mesh)
{
	myMesh = *mesh;

	//myMesh.renderer = this;
}


void GOC_MeshRenderer::SetTextures(std::vector<Texture*> textures)
{
	myMesh.textures.clear();
	for (Texture* tex : textures)
	{
		myMesh.textures.push_back(*tex);

	}

	GOC_Texture* tex = nullptr;
	tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
	if (tex != nullptr)
		tex->SetTextures(myMesh.textures);

}

void GOC_MeshRenderer::SetTextures(std::vector<Texture> textures)
{
	myMesh.textures.clear();
	for(Texture tex : textures)
	{
		myMesh.textures.push_back(tex);

	}
	
	GOC_Texture* tex = nullptr;
	tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
	if (tex != nullptr)
		tex->SetTextures(myMesh.textures);
}

void GOC_MeshRenderer::AddTextures(std::vector<Texture*> textures)
{
	for (Texture* tex : textures)
	{
		myMesh.textures.push_back(*tex);

	}

	GOC_Texture* tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
	if (tex != nullptr)
		tex->SetTextures(myMesh.textures);

}

void GOC_MeshRenderer::AddTextures(std::vector<Texture> textures)
{
	for (Texture tex : textures)
	{
		myMesh.textures.push_back(tex);

	}

	GOC_Texture* tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
	if (tex != nullptr)
		tex->SetTextures(myMesh.textures);

}

void GOC_MeshRenderer::AddTexture(Texture texture)
{
	myMesh.textures.push_back(texture);

	GOC_Texture* tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
	if (tex != nullptr)
		tex->SetTextures(myMesh.textures);

}

void GOC_MeshRenderer::Render()
{
	goCamera = (GOC_Camera*)App->engineSystem->GetAllGameObjects()[0]->GetComponent(GOC_Type::GOC_CAMERA);

	if (!myMesh.vertices.empty())
	{

		GOC_Transform* GoTransform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);

		if (gameObject->selected)
		{
			selctedShader->Use();
		}
		else
		{
			myShader->Use();
		}

		mat4x4 projection = App->renderer3D->ProjectionMatrix;
		mat4x4 view = App->camera->GetViewMatrix();
		myShader->SetMat4x4("projection", projection);
		myShader->SetMat4x4("view", view);

		myShader->SetMat4x4("model", gameObject->transform->Get4x4Matrix());

		
		if (canDraw) 
		{
			myMesh.renderer = this;
			myMesh.Draw(*myShader, App->renderer3D->atributes.Wireframe);

		}

		myShader->Unuse();
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

Mesh GOC_MeshRenderer::GetMesh() const
{
	return  myMesh;
}

bool GOC_MeshRenderer::LoadState(JSON_Value* file, std::string root)
{
	return true;
}

bool GOC_MeshRenderer::SaveState(JSON_Value* file, std::string root) const
{
	return true;
}