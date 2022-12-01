#include "GOC_MeshRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

GOC_MeshRenderer::GOC_MeshRenderer(GameObject* gameObjectAttached, mat4x4 transform)
{
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
}

void GOC_MeshRenderer::SetMesh(Mesh* mesh)
{
	myMesh = *mesh;
}


void GOC_MeshRenderer::SetTextures(std::vector<Texture*> textures)
{
	myMesh.textures.clear();
	for (Texture* tex : textures)
	{
		myMesh.textures.push_back(*tex);

	}

	GOC_Texture* tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
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
	
	GOC_Texture* tex = (GOC_Texture*)gameObject->GetComponent(GOC_Type::GOC_TEXTURE);
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

	if (!myMesh.vertices.empty())
	{

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

		//// render the loaded model
		//mat4x4 modelState = IdentityMatrix;
		//modelState.translate(gameObject->transform->GetPosition().x, gameObject->transform->GetPosition().y, gameObject->transform->GetPosition().z); // translate it down so it's at the center of the scene
		//modelState.scale(gameObject->transform->GetScale().x, gameObject->transform->GetScale().y, gameObject->transform->GetScale().z);	// it's a bit too big for our scene, so scale it down

		myShader->SetMat4x4("model", gameObject->transform->Get4x4Matrix());

		myMesh.Draw(*myShader);

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
	Render();

	return true;
}