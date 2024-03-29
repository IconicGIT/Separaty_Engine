
#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Inspector.h"
#include "GOC_Camera.h"
#include "ModuleCamera3D.h"

#include <vector>

#include <list>

#include "imgui.h"

#include "imgui_stdlib.h"

//INSPECTOR WINDOW

Inspector::Inspector()
{
	name = "Inspector";

}

Inspector::~Inspector()
{

}

update_status Inspector::Update(float dt)
{
	ImVec2 windowSize = ImVec2(0, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (App->ui->inspector)
	{
		/*WindowGameObjectInfo windowGameObjectInfo = gameObject->windowGameObjectInfo;*/
		ImGui::Begin("Inspector", &App->ui->inspector, ImGuiWindowFlags_NoMove);
        windowSize = ImVec2(App->ui->screenX / 5.5f, App->ui->screenY - 18.0f);
		ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) + 0.80f, 18.9f));
		ImGui::SetWindowSize(windowSize);

		std::string editingTypeText = "Editing Mode: ";

		std::string editingType = "Local";
		if (editingModeWorld)
			editingType = "World";

		std::string text = editingTypeText + editingType;
		if (ImGui::Checkbox(text.c_str(), &editingModeWorld))
		{
			int a = 0;
		}

		if (!UImanager->selectedGameObjects.empty())
		{
			GameObject* editorObject = UImanager->selectedGameObjects.at(UImanager->selectedGameObjects.size() - 1);
			if (!editorObject->pendingToDelete)
			{
				if (ImGui::CollapsingHeader("Information"))
				{
					ImGui::Text("Name:");
					ImGui::SameLine();

					char n[50];
					sprintf_s(n, 50, editorObject->name.c_str());
					ImGui::InputText("##Name", n, 50);

					std::vector<GameObject*> b = App->engineSystem->GetCurrentScene()->gameObjects;

					if (ImGui::Checkbox("Active", &editorObject->enabled))
					{
						int a = 0;
					}
			
				}
				// Current game object (the one we have selected at the moment)

				bool transformUpdated = false;
			
				for (GameObjectComponent* component : editorObject->GetComponents())
				{

					/*if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
					{
						editingModeWorld = false;
					}
					else
					{
						editingModeWorld = true;

					}*/

					float multiplier = 0.5f;
					switch (component->GetGOC_Type())
					{

					case GOC_Type::GOC_TRANSFORM:
					{
						if (ImGui::CollapsingHeader("Transform"))
						{

							float newPositionX = editorObject->transform->translationLocal.translation().x;
							float newPositionY = editorObject->transform->translationLocal.translation().y;
							float newPositionZ = editorObject->transform->translationLocal.translation().z;

							if (!editingModeWorld)
							{
								newPositionX = editorObject->transform->translationLocal.translation().x;
								newPositionY = editorObject->transform->translationLocal.translation().y;
								newPositionZ = editorObject->transform->translationLocal.translation().z;
							}

							float3 newPosition = vec(newPositionX, newPositionY, newPositionZ);

							ImGui::Text("Translation");
							if (ImGui::DragFloat3(" ", &newPosition[0], 0.05f, 0.0f, 0.0f, "%.2f"))
							{
								transformUpdated = true;
								this->position = newPosition;

								if (editingModeWorld)
								{
									editorObject->transform->translationLocal.translate(newPosition.x, newPosition.y, newPosition.z);
								}
								else
								{

									editorObject->transform->translationLocal.translate(newPosition.x, newPosition.y, newPosition.z);

								}
								editorObject->transform->ApplyTransformations();

							}
							if (ImGui::Button(("Reset Translation"), ImVec2(150, 20)))
							{
								editorObject->transform->ResetTranslation();
							}

							float3 newRotationEuler = editorObject->transform->rotationEulerLocal;

							if (!editingModeWorld)
								newRotationEuler = editorObject->transform->rotationEulerLocal;


							newRotationEuler.x = RADTODEG * newRotationEuler.x;
							newRotationEuler.y = RADTODEG * newRotationEuler.y;
							newRotationEuler.z = RADTODEG * newRotationEuler.z;


							ImGui::Text("Rotation");
							if (ImGui::DragFloat3("", &newRotationEuler[0], 0.05f, 0.0f, 0.0f, "%.2f"))
							{
								transformUpdated = true;

								newRotationEuler.x = DEGTORAD * newRotationEuler.x;
								newRotationEuler.y = DEGTORAD * newRotationEuler.y;
								newRotationEuler.z = DEGTORAD * newRotationEuler.z;

								if (editingModeWorld)
								{
									editorObject->transform->rotationEulerLocal = newRotationEuler;
								}
								{
									editorObject->transform->rotationEulerLocal = newRotationEuler;
								}

								Quat rotatorQuat = Quat::FromEulerXYZ(newRotationEuler.x, newRotationEuler.y, newRotationEuler.z);
								aiQuaternion rotationQuat(rotatorQuat.w, rotatorQuat.x, rotatorQuat.y, rotatorQuat.z);


								aiMatrix3x3* tempMat3 = new aiMatrix3x3;

								aiQuaternion* tempRotationQuat = new aiQuaternion(rotationQuat);

								//aiMatrix4FromScalingQuaternionPosition(tempMat, tempScale, tempRotationQuat, tempPosition);
								aiMatrix3FromQuaternion(tempMat3, tempRotationQuat);

								mat4x4 resMat = IdentityMatrix;

								resMat[0] = (float)tempMat3->a1;
								resMat[1] = (float)tempMat3->a2;
								resMat[2] = (float)tempMat3->a3;
								resMat[3] = 0;

								resMat[4] = (float)tempMat3->b1;
								resMat[5] = (float)tempMat3->b2;
								resMat[6] = (float)tempMat3->b3;
								resMat[7] = 0;

								resMat[8] = (float)tempMat3->c1;
								resMat[9] = (float)tempMat3->c2;
								resMat[10] = (float)tempMat3->c3;
								resMat[11] = 0;

								resMat[12] = 0;
								resMat[13] = 0;
								resMat[14] = 0;
								resMat[15] = 1;

								resMat.transpose();

								if (editingModeWorld)
								{
									editorObject->transform->rotationLocal = resMat;
									editorObject->transform->rotationQuatLocal = Quat(tempRotationQuat->x, tempRotationQuat->y, tempRotationQuat->z, tempRotationQuat->w);


								}
								else
								{
									editorObject->transform->rotationLocal = resMat;
									editorObject->transform->rotationQuatLocal = Quat(tempRotationQuat->x, tempRotationQuat->y, tempRotationQuat->z, tempRotationQuat->w);



								}
								editorObject->transform->ApplyTransformations();

								delete tempMat3;
								delete tempRotationQuat;

								//* 57.29578
							}

							if (ImGui::Button(("Reset Rotation"), ImVec2(150, 20)))
							{
								editorObject->transform->ResetRotation();
							}

							float newScaleX = editorObject->transform->scalingLocal.scaling().x;
							float newScaleY = editorObject->transform->scalingLocal.scaling().y;
							float newScaleZ = editorObject->transform->scalingLocal.scaling().z;
							if (!editingModeWorld)
							{
								newScaleX = editorObject->transform->scalingLocal.scaling().x;
								newScaleY = editorObject->transform->scalingLocal.scaling().y;
								newScaleZ = editorObject->transform->scalingLocal.scaling().z;
							}

							float3 newScale = vec(newScaleX, newScaleY, newScaleZ);


							ImGui::Text("Scale");
							if (ImGui::DragFloat3("  ", &newScale[0], 0.05f, 0.0f, 0.0f, "%.2f"))
							{
								transformUpdated = true;

								if (editingModeWorld)
								{
									editorObject->transform->scalingLocal.scale(newScale.x, newScale.y, newScale.z);
								}
								else
								{
									editorObject->transform->scalingLocal.scale(newScale.x, newScale.y, newScale.z);


								}
								editorObject->transform->ApplyTransformations();

							}
							if (ImGui::Button(("Reset Scale"), ImVec2(150, 20)))
							{
								editorObject->transform->ResetScale();
							}

							ImGui::Dummy(ImVec2(0, 20));

							if (ImGui::Button(("Reset Transform"), ImVec2(150, 30)))
							{
								editorObject->transform->ResetMatrices();
							}


							/*float3 debugRot = editorObject->transform->rotationEulerWorld;
							if (!editingModeWorld)
								debugRot = editorObject->transform->rotationEulerLocal;

							ImGui::Text("Editor Object Rotation:");
							ImGui::Text(std::to_string(debugRot[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugRot[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugRot[2]).c_str());

							mat4x4 debugMat1 = editorObject->transform->translationWorld;
							if (!editingModeWorld)
								debugMat1 = editorObject->transform->translationLocal;

							ImGui::Text("Translation:");
							ImGui::Text(std::to_string(debugMat1[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[2]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[3]).c_str());

							ImGui::Text(std::to_string(debugMat1[4]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[5]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[6]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[7]).c_str());

							ImGui::Text(std::to_string(debugMat1[8]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[9]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[10]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[11]).c_str());

							ImGui::Text(std::to_string(debugMat1[12]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[13]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[14]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat1[15]).c_str());


							mat4x4 debugMat2 = editorObject->transform->rotationWorld;
							if (!editingModeWorld)
								debugMat1 = editorObject->transform->rotationLocal;

							ImGui::Text("Rotation:");
							ImGui::Text(std::to_string(debugMat2[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[2]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[3]).c_str());

							ImGui::Text(std::to_string(debugMat2[4]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[5]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[6]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[7]).c_str());

							ImGui::Text(std::to_string(debugMat2[8]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[9]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[10]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[11]).c_str());

							ImGui::Text(std::to_string(debugMat2[12]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[13]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[14]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat2[15]).c_str());

							mat4x4 debugMat3 = editorObject->transform->transformWorld;
							if (!editingModeWorld)
								debugMat1 = editorObject->transform->transformLocal;

							ImGui::Text("Scaling:");
							ImGui::Text(std::to_string(debugMat3[0]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[1]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[2]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[3]).c_str());

							ImGui::Text(std::to_string(debugMat3[4]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[5]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[6]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[7]).c_str());

							ImGui::Text(std::to_string(debugMat3[8]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[9]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[10]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[11]).c_str());

							ImGui::Text(std::to_string(debugMat3[12]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[13]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[14]).c_str());
							ImGui::SameLine();
							ImGui::Text(std::to_string(debugMat3[15]).c_str());*/
						}
					}
					break;
					case GOC_Type::GOC_CAMERA:
					{
						GOC_Camera* camera = (GOC_Camera*)component;

						if (ImGui::CollapsingHeader("Camera"))
						{

							const char* camType = camera->frustum.type == PerspectiveFrustum ? "Perspective" : "Orthographic";
							ImGui::Text("Camera type: ", camType);
							ImGui::DragFloat("Far plane distance", &camera->frustum.farPlaneDistance, 10, camera->frustum.nearPlaneDistance, 2000.0f);
							ImGui::DragFloat("Near plane distance", &camera->frustum.nearPlaneDistance, 1, 0.1, camera->frustum.farPlaneDistance);

							float fov = camera->frustum.verticalFov * RADTODEG;
							if (ImGui::DragFloat("FOV", &fov, 1, 55, 120))
							{
								camera->frustum.verticalFov = fov * DEGTORAD;
								camera->frustum.horizontalFov = 2.f * atan(tan(camera->frustum.verticalFov * 0.5f) * (float(App->window->width) / App->window->height));
							}


							if (ImGui::Checkbox("Set as Main Camera", &camera->isCurrentCamera))
							{
								if (camera->isCurrentCamera)
								{
									for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
									{
										for (GameObjectComponent* comp : go->GetComponents())
										{
											if (comp->GetGOC_Type() == GOC_Type::GOC_CAMERA && editorObject->GetID() != go->GetID())
											{
												GOC_Camera* goCam = (GOC_Camera*)comp;
												goCam->isCurrentCamera = false;
											}
										}
									}
								}
							}


							useCamInPlay = camera->useCameraWhileInPlay;
							if (App->ui->uiFunctions->playStopWindow->play)
							{
								if (ImGui::Checkbox("Use Camera", &useCamInPlay))
								{
									int a = 0;
								}
							}
							else
							{
								//camera->useCameraWhileInPlay = camera->isCurrentCamera;
							}

							camera->useCameraWhileInPlay = useCamInPlay;

							App->camera->SetCamera(nullptr);
							if (camera->isCurrentCamera)
							{
								App->camera->SetCamera(camera);
							}

							//if (!App->ui->uiFunctions->playStopWindow->play)
							//{
							//	if (camera->isCurrentCamera == true)
							//	{
							//		if (ImGui::Checkbox("Editor Camera", &camera->isCurrentCamera))
							//		{
							//			camera->useCameraWhileInPlay = true;
							//			camera->isCurrentCamera = false;
							//		}
							//	}
							//	
							//	if (camera->useCameraWhileInPlay == true)
							//	{
							//		App->camera->SetCamera(nullptr);
							//		App->camera->SetCamera(camera);
							//		if (ImGui::Checkbox("Game Camera", &camera->useCameraWhileInPlay))
							//		{
							//			camera->isCurrentCamera = true;
							//			camera->useCameraWhileInPlay = false;
							//		}
							//	}




					/*		else
							{
								App->camera->SetCamera(nullptr);
								App->camera->SetCamera(camera);
								if (ImGui::Checkbox("Game Camera", &camera->useCameraWhileInPlay))
								{
									camera->isCurrentCamera = true;
									camera->useCameraWhileInPlay = false;
								}

							}*/


							ImGui::Checkbox("Draw Frustum", &camera->drawFrustum);




						}

						/*if (transformUpdated)
						{


							for (GameObject* toDraw : App->engineSystem->GetCurrentScene()->gameObjects)
							{
								GOC_MeshRenderer* renderer = nullptr;
								renderer = (GOC_MeshRenderer*)toDraw->GetComponent(GOC_Type::GOC_MESH_RENDERER);


								bool test = true;
								AABB meshBBox = renderer->GetMesh().bboxTransformed;

								test = camera->frustum.Contains(meshBBox);

								if (test)
									renderer->canDraw = true;
								else
									renderer->canDraw = false;

							}
						}*/
					}

					break;
					case GOC_Type::GOC_MESH_RENDERER:
					{
						GOC_MeshRenderer* renderer = (GOC_MeshRenderer*)component;


						if (ImGui::CollapsingHeader("Mesh Renderer"))
						{
							ImGui::Text("Mesh Name:");
							ImGui::SameLine();
							ImGui::Text(renderer->GetMesh().name.c_str());

							ImGui::Text("Material Textures:");
							if (ImGui::TreeNode("Change Mesh"))
							{
								for (Mesh m : App->engineSystem->GetAllMeshes())
								{
									if (ImGui::MenuItem(m.name.c_str()))
									{
										renderer->SetMesh(&m);
									}
								}
								ImGui::TreePop();
							}

							/*bool drawBBox = renderer->GetMesh().drawBbox;*/


						/*	if (ImGui::Checkbox("Draw Box", &renderer->GetMesh().drawBbox))
							{
								renderer->GetMesh().SetDrawBoundingBox(drawBBox);
							}*/

							/*if (ImGui::Checkbox("Draw Bounding Box", &drawBBox))
							{
								renderer->GetMesh().SetDrawBoundingBox(&drawBBox);

							}*/

							/*
							for (Texture& tex : materiatel.textures) {
								ImGui::Image((ImTextureID)tex.GetTextureId(), ImVec2(85, 85));
								ImGui::SameLine();
								ImGui::BeginGroup();
								ImGui::Text(tex.GetTexturePath());
								ImGui::PushID(tex.GetTextureId() << 8);
								if (ImGui::Button("Change Texture")) {
									panelChooser->OpenPanel("ChangeTexture", "png");
									currentTextureId = tex.GetTextureId();
							}
							ImGui::PopID();

							ImGui::PushID(tex.GetTextureId() << 16);

							if (ImGui::Button("Delete Textures")) {
								material.textures.erase(std::remove(material.textures.begin(), material.textures.end(), tex));
							}

							ImGui::PopID();
							ImGui::EndGroup();

							}
							if (ImGui::Button("Add Texture")) {
								panelChooser->OpenPanel("AddTexture", "png");

							}
							ImGui::Separator();
							if (ImGui::Button("Change Shader")) {
								panelChooser->OpenPanel("ChangeShader","glsl");
							}

							*/

						}
					}
					break;
					case GOC_Type::GOC_TEXTURE:
					{
						GOC_Texture* texture = (GOC_Texture*)component;

						if (ImGui::CollapsingHeader("Texture"))
						{
							std::string test = "N. textures: " + std::to_string(texture->GetTextures().size());
							ImGui::Text(test.c_str());
							if (texture->GetTextures().size() > 0)
							{

								for (Texture* tex : texture->GetTextures())
								{
									std::string texName = "Texture name: " + tex->name;
									ImGui::Text(texName.c_str());

									ImGui::Image((ImTextureID)tex->id, ImVec2(85, 85));
								}
							}
							else
							{
								ImGui::Text("No texture loaded.");
							}

							//ImGui::Image((ImTextureID)texture->GetTexture(), ImVec2(85, 85));
							ImGui::SameLine();
							ImGui::BeginGroup();
							/*ImGui::Text(texture->GetTexture()->name.c_str());
							ImGui::PushID(texture->GetTexture()->id << 8);*/

							if (ImGui::Button("Change Texture")) {
								/*panelChooser->OpenPanel("ChangeTexture", "png");
								currentTextureId = tex.GetTexture();*/
								OPENFILENAMEA ofn;
								char fileName[MAX_PATH] = "";
								ZeroMemory(&ofn, sizeof(ofn));
								ofn.lStructSize = sizeof(OPENFILENAMEA);
								ofn.hwndOwner = NULL;
								ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
								ofn.lpstrFile = fileName;
								ofn.nMaxFile = MAX_PATH;
								ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
								ofn.lpstrDefExt = "";

								GetOpenFileNameA(&ofn);
								if (fileName[0] != '\0')
								{
									App->engineSystem->LoadFromPath(fileName);
								}

								std::string path_s = fileName;
								int lastBar = path_s.find_last_of("\\\"");
								if (lastBar == -1)
								{
									lastBar = path_s.find_last_of("/");
								}

								std::string newTex_name = path_s.substr(lastBar + 1);



								for (Texture tex : App->engineSystem->GetAllTextures())
								{

									if (std::strcmp(tex.name.c_str(), newTex_name.c_str()) == 0)
									{
										texture->SetTexture(tex);
										texture->UpdateMeshRendererTexture(true);
										break;
									}
								}
							}
							/*ImGui::PopID();*/

							/*ImGui::PushID(texture->GetTexture() << 16);*/
							ImGui::Dummy(ImVec2(0, 0));
							if (ImGui::Button("Delete Texture"))
							{
								for (Texture tex : App->engineSystem->GetAllTextures())
								{
									if (std::strcmp(tex.name.c_str(), "default_texture.png") == 0)
									{
										texture->SetTexture(tex);
										texture->UpdateMeshRendererTexture(true);
										break;
									}
								}
							}
							/*ImGui::PopID();*/

							ImGui::EndGroup();


							if (ImGui::Button("Show Checker Texture")) {

								for (Texture tex : App->engineSystem->GetAllTextures())
								{
									if (std::strcmp(tex.name.c_str(), "checker_pattern.png") == 0)
									{
										texture->SetTexture(tex);
										texture->UpdateMeshRendererTexture(true);
										break;
									}
								}
								/*Texture a = ;
								texture->SetTexture(a);
								texture->UpdateMeshRendererTexture();*/
							}
							ImGui::Separator();

							if (ImGui::TreeNode("Change Texture:"))
							{
								for (Texture t : App->engineSystem->GetAllTextures())
								{
									if (ImGui::MenuItem(t.name.c_str()))
									{
										texture->SetTexture(t);
										texture->UpdateMeshRendererTexture(true);
									}
								}
								ImGui::TreePop();
							}
							/*if (texture->GetTexture() != nullptr)
							{
								ImGui::Text("Texture data:");
								ImGui::Text("Width:  1024");
								ImGui::Text("Height: 1024");
							}*/

						}

					}
					break;
					case GOC_Type::GOC_PARTICLE_EMITTER:
					{
						GOC_ParticleEmitter* comp = (GOC_ParticleEmitter*)component;
						
						if (ImGui::CollapsingHeader("Particle Emitter"))
						{
							for (std::shared_ptr<Submodule> submod : comp->emitter->submodules)
							{
								//std::string nParticles = "n. Active Particles: " + comp->emitter->particles.size();
								ImGui::TextColored(ImVec4(1, 1, 0, 1), "N. Active Particles: %i", comp->emitter->particles.size());
								
								std::string submodName = "Particle Set Data";
								ImGui::Separator();

								if (ImGui::TreeNode(submodName.c_str()))
								{
									ImGui::Separator();
									ImGui::Text("Module attributes");
									ImGui::Separator();
									ImGui::Text("Range");

									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox(" ##1", &submod->particle_rate_isRanged);
									ImGui::SameLine();
									ImGui::Text("Spawn Rate");
									if (submod->particle_rate_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::PushItemWidth(46.0f);
										ImGui::DragFloat("##11", &submod->particle_rate_range[0], 0.01f, 0.0f, 0.0f, "%.2f");
										ImGui::SameLine();
										ImGui::DragFloat("##12", &submod->particle_rate_range[1], 0.01f, 0.0f, 0.0f, "%.2f");
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::PushItemWidth(100.0f);
										ImGui::DragFloat("##10", &submod->particle_rate, 0.05f, 0.0f, 0.0f, "%.2f");
									}
									ImGui::PopItemWidth();
									

									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox(" ##2", &submod->particle_amount_isRanged);
									ImGui::SameLine();
									ImGui::Text("Spawn Amount");
									if (submod->particle_amount_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::PushItemWidth(46.0f);
										ImGui::DragInt("##21", &submod->particle_amount_range[0], 0.05f, 0.0f, 0.0f, "%.2f");
										ImGui::SameLine();
										ImGui::DragInt("##22", &submod->particle_amount_range[1], 0.05f, 0.0f, 0.0f, "%.2f");
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::PushItemWidth(100.0f);
										ImGui::DragInt("##20", &submod->particle_amount, 0.05f, 0.0f, 0.0f, "%.2f");
									}
									ImGui::PopItemWidth();
									

									ImGui::Separator();
									ImGui::Text("Particle attributes");
									ImGui::Separator();

									ImGui::Text("Range");

									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox("##200", &submod->particle_followEmitter);
									ImGui::SameLine();
									ImGui::Dummy(ImVec2(2.5, 0));
									ImGui::SameLine();
									ImGui::Text("Follow Emitter");

									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox(" ##3", &submod->particle_lifetime_isRanged);
									ImGui::SameLine();
									ImGui::Text("Particle life time");

									if (submod->particle_lifetime_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::PushItemWidth(46.0f);
										ImGui::DragFloat("##31", &submod->particle_lifetime_range[0], 0.05f, 0.0f, 0.0f, "%.2f");
										ImGui::SameLine();
										ImGui::DragFloat("##32", &submod->particle_lifetime_range[1], 0.05f, 0.0f, 0.0f, "%.2f");
									
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::PushItemWidth(100.0f);
										ImGui::DragFloat("##300", &submod->particle_lifetime, 0.05f, 0.0f, 0.0f, "%.2f");
										
									}
									ImGui::PopItemWidth();
									
									
									
									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox("##7", &submod->particle_originPosition_isRanged);
									ImGui::SameLine();
									ImGui::Dummy(ImVec2(2, 0));
									ImGui::SameLine();
									ImGui::Text("Particle Origin");
									if (submod->particle_originPosition_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##71", &(submod->particle_originPosition_range[0])[0], 0.05f, 0.0f, 0.0f, "%.2f");
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##72", &(submod->particle_originPosition_range[1])[0], 0.05f, 0.0f, 0.0f, "%.2f");
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##7", &(submod->particle_originPosition)[0], 0.05f, 0.0f, 0.0f, "%.2f");
									}



									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox(" ##4", &submod->particle_velocity_isRanged);
									ImGui::SameLine();
									ImGui::Text("Particle Velocity");
									if (submod->particle_velocity_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##41", &(submod->particle_velocity_range[0])[0], 0.05f, 0.0f, 0.0f, "%.2f");
									/*	ImGui::SameLine();
										ImGui::Text("Particle Velocity");*/
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##42", &(submod->particle_velocity_range[1])[0], 0.05f, 0.0f, 0.0f, "%.2f");
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##4", &(submod->particle_velocity)[0], 0.05f, 0.0f, 0.0f, "%.2f");
										/*ImGui::SameLine();
										ImGui::Text("Particle Velocity");*/
									}
									
									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox(" ##5", &submod->particle_acceleration_isRanged);
									ImGui::SameLine();
									ImGui::Text("Particle Acceleration");
									if (submod->particle_acceleration_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##51", &(submod->particle_acceleration_range[0])[0], 0.01f, 0.0f, 0.0f, "%.2f");
										/*ImGui::SameLine();
										ImGui::Text("Particle Acceleration");*/
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##52", &(submod->particle_acceleration_range[1])[0], 0.01f, 0.0f, 0.0f, "%.2f");
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##5", &(submod->particle_acceleration)[0], 0.01f, 0.0f, 0.0f, "%.2f");
										/*ImGui::SameLine();
										ImGui::Text("Particle Acceleration");*/
									}
									
									ImGui::Dummy(ImVec2(0, 0));
									ImGui::SameLine();
									ImGui::Checkbox(" ##6", &submod->particle_direction_isRanged);
									ImGui::SameLine();
									ImGui::Text("Particle Direction");
									if (submod->particle_direction_isRanged)
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##61", &(submod->particle_direction_range[0])[0], 0.05f, 0.0f, 0.0f, "%.2f");
										/*ImGui::SameLine();
										ImGui::Text("Particle Direction");*/
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##62", &(submod->particle_direction_range[1])[0], 0.05f, 0.0f, 0.0f, "%.2f");
									}
									else
									{
										ImGui::Dummy(ImVec2(38, 0));
										ImGui::SameLine();
										ImGui::DragFloat3("##6", &submod->particle_direction[0], 0.05f, 0.0f, 0.0f, "%.2f");
										/*ImGui::SameLine();
										ImGui::Text("Particle Direction");*/
									}
									
									//fixers

									if (submod->particle_rate < 0) submod->particle_rate = 0.01f;
									if (submod->particle_rate < 0) submod->particle_amount = 0;
									if (submod->particle_lifetime < 0) submod->particle_lifetime = 0;

									ImGui::TreePop();
								}
								ImGui::Separator();
								if (ImGui::TreeNode("Particle Shape"))
								{
									ImGui::Separator();
									float3 pos;
									if (boxShape)
									{
										ImGui::Text("Box");
										ImGui::SameLine();
										ImGui::Checkbox("##500", &activeBox);
										ImGui::Separator();
										ImGui::Text("Particle emision from:");

										//pos = boxCreation.Size();

										if (ImGui::RadioButton("Random", randomBEmision))
										{
											randomBEmision = true;
											CenterBEmision = false;
											BorderBEmision = false;
										}

										if (ImGui::RadioButton("Center", CenterBEmision))
										{
											randomBEmision = false;
											CenterBEmision = true;
											BorderBEmision = false;
										}		  
												  
										if (ImGui::RadioButton("Border", BorderBEmision))
										{		  
											randomBEmision = false;
											CenterBEmision = false;
											BorderBEmision = true;
										}

										ImGui::DragFloat3("Box Size", &pos.x, 0.1f, 0.1f, 20.0f, "%.2f");

										boxCreation.SetFromCenterAndSize(boxCreation.CenterPoint(), pos);
									}
									else if (sphereShape)
									{
										ImGui::Text("Sphere");
										ImGui::Separator();
										ImGui::Text("Particle emision from:");

										if (ImGui::RadioButton("Random", randomSEmision))
										{
											randomSEmision = true;
											CenterSEmision = false;
											BorderSEmision = false;
										}
											
										if (ImGui::RadioButton("Center", CenterSEmision))
										{
											randomSEmision = false;
											CenterSEmision = true;
											BorderSEmision = false;
										}
											
										if (ImGui::RadioButton("Border", BorderSEmision))
										{
											randomSEmision = false;
											CenterSEmision = false;
											BorderSEmision = true;
										}
											
										ImGui::DragFloat("Sphere Size", &sphereCreation.r, 0.25f, 1.0f, 20.0f, "%.2f");
									}
									else if (coneShape)
									{
										ImGui::Text("Cone");
										ImGui::Separator();
										ImGui::Text("Particle emision from:");

										if (ImGui::RadioButton("Random", randomCEmision))
										{
											randomCEmision = true;
											CenterCEmision = false;
											BorderCEmision = false;
										}

										if (ImGui::RadioButton("Center", CenterCEmision))
										{
											randomCEmision = false;
											CenterCEmision = true;
											BorderCEmision = false;
										}

										if (ImGui::RadioButton("Border", BorderCEmision))
										{
											randomCEmision = false;
											CenterCEmision = false;
											BorderCEmision = true;
										}

										ImGui::DragFloat("Sphere Size", &circleCreation.r, 0.25f, 0.25f, 20.0f, "%.2f");
									}

									ImGui::Separator();
									if (ImGui::TreeNode("Change Shape"))
									{
										ImGui::Separator();
										if (ImGui::MenuItem("Box"))
										{
											boxShape = true;
											sphereShape = false;
											coneShape = false;
										}
										else if (ImGui::MenuItem("Sphere"))
										{
											boxShape = false;
											sphereShape = true;
											coneShape = false;
										}
										else if (ImGui::MenuItem("Cone"))
										{
											boxShape = false;
											sphereShape = false;
											coneShape = true;
										}
										ImGui::TreePop();
									}

									ImGui::TreePop();
								}						
								ImGui::Separator();
								
								if (ImGui::TreeNode("Particle Color"))
								{
									ImGui::Separator();
									if (noColors)
									{
										ColorTime colorTime;
										colorTime.position = (float)submod->nextPos / 100;
										colorTime.name = std::to_string((int)submod->nextPos) + "%";
										submod->particle_color.push_back(colorTime);
										submod->particle_color.sort();

										noColors = false;
									}
									ImGui::Text("Start Color");
									ImGui::SameLine();
									std::vector<ColorTime> deleteColor;
									std::list<ColorTime>::iterator iter = submod->particle_color.begin();
									uint posList = 0u;
									while (iter != submod->particle_color.end())
									{
										if ((iter) == submod->particle_color.begin())
										{//Cant delete 1st color

											if (!submod->emitter->EditColor(*iter))
												break;
											iter++;
										}
										else
										{
											if (!submod->emitter->EditColor(*iter, posList))
												submod->particle_color.erase(iter++);
											else
												iter++;
										}
										++posList;
									}
									ImGui::Separator();
									if (ImGui::TreeNode("Add Color "))
									{
										ImGui::Separator();
										submod->emitter->timeColor = true;

										if (submod->emitter->timeColor)
										{
											std::string colorPercentage = "Color At: " + std::to_string(submod->nextPos);
											ImGui::Text(colorPercentage.c_str());
											ImGui::SameLine();
											ImGui::Text("%");
											ImGui::DragInt(" ", &submod->nextPos, 1.0f, 1, 100);
											ImGui::ColorPicker4("", &submod->nextColor.x, ImGuiColorEditFlags_AlphaBar);
											if (ImGui::Button("Add Color", ImVec2(125, 25)))
											{
												ColorTime colorTime;
												colorTime.color = submod->nextColor;
												colorTime.position = (float)submod->nextPos / 100;
												colorTime.name = std::to_string((int)submod->nextPos) + "%";
												submod->particle_color.push_back(colorTime);
												submod->particle_color.sort();
											}
										}
										ImGui::TreePop();
									}
									ImGui::TreePop();
								}
								ImGui::Separator();
								if (ImGui::TreeNode("Particle Bounding Box"))
								{
									ImGui::Separator();

									ImGui::TreePop();
								}
								ImGui::Separator();
								if (ImGui::TreeNode("Particle Texture"))
								{
									ImGui::Separator();
									if (submod->particle_textureReference)
									{


										std::string texName = "Texture name: " + submod->particle_textureReference->name;
										ImGui::Text(texName.c_str());

										ImVec2 pos = ImGui::GetCursorScreenPos();
										float image_size = 84;
										
										//if (submod->particle_textures.size() > 0)
										//{
										//	/*int amount = submod->particle_texture_amountUsing;
										//	int amountH = submod->particle_texture_rowsColumnsUsing[0];
										//	int amountV = submod->particle_texture_rowsColumnsUsing[1];

										//	int amountIndex = 0;
										//	for (size_t v = 0; v < amountV; v++)
										//	{
										//		for (size_t h = 0; h < amountH; h++)
										//		{
										//			if (amountIndex < amount)
										//			{
										//				float a1 = pos.x + h * int(image_size / amountH);
										//				float b1 = pos.x + h * int(image_size / amountH) + int(image_size / amountH);

										//				float a2 = pos.y + v * int(image_size / amountV);
										//				float b2 = pos.y + v * int(image_size / amountV) + int(image_size / amountV);


										//				draw_list->AddRectFilled(
										//					ImVec2(a1, a2),
										//					ImVec2(b1, b2),
										//					IM_COL32(102, 255, 102, 50),
										//					0.0f,
										//					ImDrawCornerFlags_None);

										//				draw_list->AddRect(
										//					ImVec2(a1, a2),
										//					ImVec2(b1, b2),
										//					IM_COL32(153, 255, 153, 50),
										//					0.0f,
										//					ImDrawCornerFlags_None,
										//					1.f);

										//				amountIndex++;
										//			}
										//			else
										//			{
										//				break;
										//			}
										//		}
										//		if (!(amountIndex < amount)) break;
										//	}*/

										//	float h_ = float(submod->particle_textures[0]->height) / float(submod->particle_textureReference->height) * image_size;
										//	float w_ = float(submod->particle_textures[0]->width) / float(submod->particle_textureReference->width) * image_size;

										//	ImGui::Image((void*)(intptr_t)submod->particle_textures[0]->id, ImVec2(w_, h_));
										//}
										//else
										//{
										//	ImGui::Image((ImTextureID)15, ImVec2(image_size, image_size));
										//}
										ImGui::Image((ImTextureID)submod->particle_textureReference->id, ImVec2(image_size, image_size));

										ImDrawList* draw_list = ImGui::GetWindowDrawList();
										if (submod->particle_texture_isSliced)
										{
											int amount = submod->particle_texture_amountUsing;
											int amountH = submod->particle_texture_rowsColumnsUsing[0];
											int amountV = submod->particle_texture_rowsColumnsUsing[1];

											int amountIndex = 0;
											
											if (submod->particle_texture_amountToSet == submod->particle_texture_amountUsing &&
												submod->particle_texture_rowsColumnsToSet[0] == submod->particle_texture_rowsColumnsUsing[0] &&
												submod->particle_texture_rowsColumnsToSet[1] == submod->particle_texture_rowsColumnsUsing[1])
											{
												for (size_t v = 0; v < amountV; v++)
												{
													for (size_t h = 0; h < amountH; h++)
													{
														if (amountIndex < amount)
														{
															float a1 = pos.x + h * int(image_size / amountH);
															float b1 = pos.x + h * int(image_size / amountH) + int(image_size / amountH);

															float a2 = pos.y + v * int(image_size / amountV);
															float b2 = pos.y + v * int(image_size / amountV) + int(image_size / amountV);


															draw_list->AddRectFilled(
																ImVec2(a1, a2),
																ImVec2(b1, b2),
																IM_COL32(102, 255, 102, 100),
																0.0f,
																ImDrawCornerFlags_None);

															draw_list->AddRect(
																ImVec2(a1, a2),
																ImVec2(b1, b2),
																IM_COL32(153, 255, 153, 100),
																0.0f,
																ImDrawCornerFlags_None,
																1.f);

															amountIndex++;
														}
														else
														{
															break;
														}
													}
													if (!(amountIndex < amount)) break;
												}
											}
											else
											{
												amount = submod->particle_texture_amountToSet;
												amountH = submod->particle_texture_rowsColumnsToSet[0];
												amountV = submod->particle_texture_rowsColumnsToSet[1];

												amountIndex = 0;
												for (size_t v = 0; v < amountV; v++)
												{
													for (size_t h = 0; h < amountH; h++)
													{
														if (amountIndex < amount)
														{
															float a1 = pos.x + h * int(image_size / amountH);
															float b1 = pos.x + h * int(image_size / amountH) + int(image_size / amountH);

															float a2 = pos.y + v * int(image_size / amountV);
															float b2 = pos.y + v * int(image_size / amountV) + int(image_size / amountV);

															draw_list->AddRect(
																ImVec2(a1, a2),
																ImVec2(b1, b2),
																IM_COL32(0, 204, 255, 75),
																0.0f,
																ImDrawCornerFlags_All,
																0.5f);

															amountIndex++;
														}
														else
														{
															break;
														}
													}
													if (!(amountIndex < amount)) break;
												}
											}
										}
									}
									else
									{
										ImGui::Text("No texture loaded.");
									}

									//ImGui::Image((ImTextureID)texture->GetTexture(), ImVec2(85, 85));
									ImGui::SameLine();
									ImGui::BeginGroup();
									/*ImGui::Text(texture->GetTexture()->name.c_str());
									ImGui::PushID(texture->GetTexture()->id << 8);*/

									if (ImGui::Button("Change Texture")) {
										/*panelChooser->OpenPanel("ChangeTexture", "png");
										currentTextureId = tex.GetTexture();*/
										OPENFILENAMEA ofn;
										char fileName[MAX_PATH] = "";
										ZeroMemory(&ofn, sizeof(ofn));
										ofn.lStructSize = sizeof(OPENFILENAMEA);
										ofn.hwndOwner = NULL;
										ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
										ofn.lpstrFile = fileName;
										ofn.nMaxFile = MAX_PATH;
										ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
										ofn.lpstrDefExt = "";

										GetOpenFileNameA(&ofn);
										if (fileName[0] != '\0')
										{
											App->engineSystem->LoadFromPath(fileName);
										}

										std::string path_s = fileName;
										int lastBar = path_s.find_last_of("\\\"");
										if (lastBar == -1)
										{
											lastBar = path_s.find_last_of("/");
										}

										std::string newTex_name = path_s.substr(lastBar + 1);



										for (Texture tex : App->engineSystem->GetAllTextures())
										{

											if (std::strcmp(tex.name.c_str(), newTex_name.c_str()) == 0)
											{
												submod->particle_textureReference->height = tex.height;
												submod->particle_textureReference->id = tex.id;
												submod->particle_textureReference->name = tex.name;
												submod->particle_textureReference->nrChannels = tex.nrChannels;
												submod->particle_textureReference->path = tex.path;
												submod->particle_textureReference->type = tex.type;
												submod->particle_textureReference->width = tex.width;

												break;
											}
										}
									}
									/*ImGui::PopID();*/

									/*ImGui::PushID(texture->GetTexture() << 16);*/
									ImGui::Dummy(ImVec2(0, 0));
									if (ImGui::Button("Delete Texture"))
									{
										for (Texture tex : App->engineSystem->GetAllTextures())
										{
											if (std::strcmp(tex.name.c_str(), "default_texture.png") == 0)
											{
												submod->particle_textureReference->height = tex.height;
												submod->particle_textureReference->id = tex.id;
												submod->particle_textureReference->name = tex.name;
												submod->particle_textureReference->nrChannels = tex.nrChannels;
												submod->particle_textureReference->path = tex.path;
												submod->particle_textureReference->type = tex.type;
												submod->particle_textureReference->width = tex.width;
												break;
											}
										}
									}
									/*ImGui::PopID();*/

									ImGui::EndGroup();


									if (ImGui::Button("Show Checker Texture")) {

										for (Texture tex : App->engineSystem->GetAllTextures())
										{
											if (std::strcmp(tex.name.c_str(), "checker_pattern.png") == 0)
											{
												submod->particle_textureReference->height = tex.height;
												submod->particle_textureReference->id = tex.id;
												submod->particle_textureReference->name = tex.name;
												submod->particle_textureReference->nrChannels = tex.nrChannels;
												submod->particle_textureReference->path = tex.path;
												submod->particle_textureReference->type = tex.type;
												submod->particle_textureReference->width = tex.width;
												break;
											}
										}
										/*Texture a = ;
										texture->SetTexture(a);
										texture->UpdateMeshRendererTexture();*/
									}
									ImGui::Dummy(ImVec2(0, 5));

									ImGui::Checkbox("Multiple Texture", &submod->particle_texture_isSliced);

									if (submod->particle_texture_isSliced)
									{
										ImGui::Text("Rows & Columns");
										ImGui::PushItemWidth(46.0f);
										if (ImGui::DragInt("##81", &submod->particle_texture_rowsColumnsToSet[0], 0.05f, 0.0f, 0.0f, "%.2f"))
										{
											submod->particle_texture_amountToSet = submod->particle_texture_rowsColumnsToSet[0] * submod->particle_texture_rowsColumnsToSet[1];
										}
										ImGui::SameLine();
										if (ImGui::DragInt("##82", &submod->particle_texture_rowsColumnsToSet[1], 0.05f, 0.0f, 0.0f, "%.2f"))
										{
											submod->particle_texture_amountToSet = submod->particle_texture_rowsColumnsToSet[0] * submod->particle_texture_rowsColumnsToSet[1];
										}
										std::string setRowCol = "Using: " + std::to_string(submod->particle_texture_rowsColumnsUsing[0]) + " , " + std::to_string(submod->particle_texture_rowsColumnsUsing[1]);
										ImGui::Text(setRowCol.c_str());

										ImGui::Dummy(ImVec2(0, 5));
										ImGui::PopItemWidth();

										ImGui::Text("Amount");
										ImGui::PushItemWidth(46.0f);
										ImGui::DragInt("##83", &submod->particle_texture_amountToSet, 0.05f, 0.0f, 0.0f, "%.2f");
										ImGui::SameLine();
										if (ImGui::Button("Slice & Attach"))
										{
											submod->SetTextureSliceData();
											comp->SetSubmoduleTexture(submod->particle_textureReference, submod);

										}
										std::string setAmount = "Using: " + std::to_string(submod->particle_texture_amountUsing);
										ImGui::Text(setAmount.c_str());

										ImGui::PopItemWidth();

									}
									else
									{
										if (ImGui::Button("Attach"))
										{
											comp->SetSubmoduleTexture(submod->particle_textureReference, submod);
										}
									}

									if (submod->particle_texture_rowsColumnsToSet[0] < 1) submod->particle_texture_rowsColumnsToSet[0] = 1;
									if (submod->particle_texture_rowsColumnsToSet[1] < 1) submod->particle_texture_rowsColumnsToSet[1] = 1;
									if (submod->particle_texture_amountToSet < 1) submod->particle_texture_amountToSet = submod->particle_texture_rowsColumnsToSet[0] * submod->particle_texture_rowsColumnsToSet[1];

									int p_tex_rc_max_am = submod->particle_texture_rowsColumnsToSet[0] * submod->particle_texture_rowsColumnsToSet[1];
									if (submod->particle_texture_amountToSet > p_tex_rc_max_am) submod->particle_texture_amountToSet = p_tex_rc_max_am;

									ImGui::TreePop();
								}
								ImGui::Separator();
							}
						}
						
					}
					break;
					}
					
				}
			}
			/*for (GameObject* go : UImanager->selectedGameObjects)
			{

				go->CopyFromGameObject(*editorObject);

			}*/
		}
		ImGui::End();
	}
	return UPDATE_CONTINUE;
}

//float3 Inspector::RandPos()
//{
//	float3 spawn = float3::zero;
//	float angle = 0.0f;
//	float centerDist = 0.0f;
//
//	if (boxShape)
//	{
//		spawn = boxCreation.RandomPointInside(randomMath);
//		 = (float3::unitY * gameObject->transform->GetRotation().ToFloat3x3()).Normalized();
//	}
//	
//
//}

//Inspector
//void UIFunctions::SetPosition(const float3& newPosition)
//{
//	position = newPosition;
//}

//void UIFunctions::SetRotation(const float3& newRotation)
//{
//	Quat rotationDelta = Quat::FromEulerXYZ(newRotation.x - rotationEuler.x, newRotation.y - rotationEuler.y, newRotation.z - rotationEuler.z);
//	rotation = rotation * rotationDelta;
//	rotationEuler = newRotation;
//}
//
//void UIFunctions::SetScale(const float3& newScale)
//{
//	selectedGameObject->transform->SetScale(newScale.x, newScale.y, newScale.z);
//}


