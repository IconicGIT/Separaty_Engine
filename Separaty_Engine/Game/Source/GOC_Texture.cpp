#include "GOC_Texture.h"


void GOC_Texture::UpdateMeshRendererTexture(bool updateInGameObjectChildren)
{
	GOC_MeshRenderer* renderer = nullptr;
	renderer = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	
	if (renderer != nullptr)
	{
		renderer->SetTextures(textures);
	}

	if (updateInGameObjectChildren)
	{
		for (GameObject* child : gameObject->GetChildren())
		{
			GOC_MeshRenderer* renderer = nullptr;
			renderer = (GOC_MeshRenderer*)child->GetComponent(GOC_Type::GOC_MESH_RENDERER);
			renderer->SetTextures(textures);
		}
	}
}


bool GOC_Texture::SaveState(JSON_Value* file, std::string root) const
{
	json_object_dotset_number(json_object(file), std::string(root + "count").c_str(), textures.size());

	for (Texture* tex : textures)
	{
		json_object_dotset_string(json_object(file), std::string(root + "name").c_str(), tex->name.c_str());
		json_object_dotset_string(json_object(file), std::string(root + "texture_path").c_str(), tex->path.c_str());

	}
	return true;
}

bool GOC_Texture::LoadState(JSON_Value* file, std::string root)
{

	int count = (int)json_object_dotget_number(json_object(file), std::string(root + "count").c_str());

	for (size_t i = 0; i < count; i++)
	{
		Texture tex;
		tex.name = json_object_dotget_string(json_object(file), std::string(root + "name").c_str());
		

		if (tex.name != std::string(""))
		{
			bool success = false;
			for (Texture t : App->engineSystem->GetAllTextures())
			{
				if (t.name == tex.name)
				{
					tex = t;
					success = true;
				}
			}

			if (!success)
			{
				std::string path = json_object_dotget_string(json_object(file), std::string(root + "texture_path").c_str());

				App->engineSystem->LoadFromPath((char*)path.c_str(), false);

				for (Texture t : App->engineSystem->GetAllTextures())
				{
					if (t.name == tex.name)
					{
						tex = t;
						success = true;
					}
				}
			}

			if (!success)
				App->ui->AppendToOutput(DEBUG_LOG("Failed loading [%s]. Path[%s]", tex.name.c_str(), tex.path.c_str()));
			else
			{
				AddTexture(tex);
				SetTexture(tex);
				UpdateMeshRendererTexture();
			}
		}
	}

	return true;
}

