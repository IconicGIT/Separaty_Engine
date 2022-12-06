#include "Globals.h"
#include "Application.h"
#include "UIFunctions.h"
#include "GameObject.h"
#include "GameObjComponent.h"
#include "GOC_Transform.h"
#include "GOC_MeshRenderer.h"
#include "GOC_Texture.h"
#include "ComponentCamera.h"

#include "imgui_stdlib.h"
#include "scene.h"

#include "EngineSystem.h"

#include "ModuleUI.h"

std::string WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

UIFunctions::UIFunctions()
{
	ghostObject = App->engineSystem->CreateNewGameObject();
}

UIFunctions::~UIFunctions()
{

}

bool UIFunctions::Start()
{
	showPreferences = new Preferences();
	showPreferences->Start();

	return true;
}

update_status UIFunctions::Update(float dt)
{
	ImVec2 windowSize = ImVec2(0,0); 

	//PROJECT PREFERENCES
	showPreferences->Update(dt);
	

	//App DATA 
	if (App->ui->showApplicationData)
	{
		ImGui::Begin("Show Application Data", &App->ui->showApplicationData);

		
		if (ImGui::CollapsingHeader("Application"))
		{
			//AppNameDisplay
			sprintf_s(App->ui->inputs, 20, TITLE);
			ImGui::InputText("App Name", App->ui->inputs, 20);
			//OrganizationNameDisplay (Citm)
			sprintf_s(App->ui->inputs, 20, ORGANITZATION);
			ImGui::InputText("Organization", App->ui->inputs, 20);
			//MaxFPSSlider
			ImGui::SliderInt("Max FPS", &App->window->maxFPS, 1, 60);
			//LimitFramerateText Limit Framereate: %d
			ImGui::Text("Limit Framerate: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", App->window->maxFPS);
			//FPSGraph
			App->window->FPSGraph(dt, 100);
			//MillisecondsGraph
			App->window->MSGraph(dt, 100);
		}


		// Hardware 
		if (ImGui::CollapsingHeader("Hardware"))
		{
			SDL_version version;
			SDL_GetVersion(&version);
			ImGui::Text("SDL Version:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d.%d.%d", version.major, version.minor, version.patch);
			ImGui::Separator();
			ImGui::Text("CPU:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d(Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
			ImGui::Text("System RAM:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.1f", (float)(SDL_GetSystemRAM() / 1024));
			ImGui::Text("Caps: ");

			if (SDL_HasRDTSC() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "RDTSC,");
			}
			if (SDL_HasMMX() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "MMX,");
			}
			if (SDL_HasSSE() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE,");
			}
			if (SDL_HasSSE2() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE2,");
			}
			if (SDL_HasSSE3() == SDL_bool::SDL_TRUE)
			{
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE3,");
			}
			if (SDL_HasSSE41() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE41,");
			}
			if (SDL_HasSSE42() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE41,");
			}
			if (SDL_HasAVX() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "AVX,");
			}
			if (SDL_HasAVX2() == SDL_bool::SDL_TRUE)
			{
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "AVX2");
			}
			ImGui::Separator();

			const GLubyte* vendor = glGetString(GL_VENDOR);
			const GLubyte* renderer = glGetString(GL_RENDERER);

			ImGui::Text("GPU:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", vendor);

			ImGui::Text("Brand:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", renderer);

			GLint parameter = 0;
			ImGui::Text("VRAM budget:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dMB", parameter / 1024);

			ImGui::Text("VRAM usage:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dMB", parameter / 1024);

			//glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &parameter);
			ImGui::Text("VRAM available:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dMB", parameter / 1024);

			ImGui::Text("VRAM reserved:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%dMB", parameter / 1024);
		}

		//INPUTS 
		if (ImGui::CollapsingHeader("Inputs & Navigation"))
		{
			ImGuiIO& io = ImGui::GetIO();


			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Mouse State"))
			{
				// Display Mouse state

				if (ImGui::IsMousePosValid())
				{
					ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
				}
				else
				{
					ImGui::Text("Mouse pos: <INVALID>");
				}
				ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);

				int count = IM_ARRAYSIZE(io.MouseDown);
				ImGui::Text("Mouse down:");         for (int i = 0; i < count; i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
				ImGui::Text("Mouse clicked:");      for (int i = 0; i < count; i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d (%d)", i, ImGui::GetMouseClickedCount(i)); }
				ImGui::Text("Mouse released:");     for (int i = 0; i < count; i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
				ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
				ImGui::Text("Pen Pressure: %.1f", io.PenPressure); // Note: currently unused
				ImGui::TreePop();
			}
			ImGui::Separator();
			// Display Keyboard/Mouse state
			if (ImGui::TreeNode("Keyboard, Gamepad & Navigation State"))
			{
				// We iterate both legacy native range and named ImGuiKey ranges, which is a little odd but this allows displaying the data for old/new backends.
				// User code should never have to go through such hoops: old code may use native keycodes, new code may use ImGuiKey codes.
#ifdef IMGUIDISABLE_OBSOLETE_KEYIO
				struct funcs { static bool IsLegacyNativeDupe(ImGuiKey) { return false; } };
				const ImGuiKey key_first = (ImGuiKey)ImGuiKey_NamedKey_BEGIN;
#else
				struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
				const ImGuiKey key_first = (ImGuiKey)0;
				//ImGui::Text("Legacy raw:");       for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++) { if (io.KeysDown[key]) { ImGui::SameLine(); ImGui::Text("\"%s\" %d", ImGui::GetKeyName(key), key); } }
#endif
				ImGui::Text("Keys down:");          for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key)) continue; if (ImGui::IsKeyDown(key)) { ImGui::SameLine(); ImGui::Text("\"%s\" %d (%.02f secs)", ImGui::GetKeyName(key), key, ImGui::GetKeyData(key)->DownDuration); } }
				ImGui::Text("Keys pressed:");       for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key)) continue; if (ImGui::IsKeyPressed(key)) { ImGui::SameLine(); ImGui::Text("\"%s\" %d", ImGui::GetKeyName(key), key); } }
				ImGui::Text("Keys released:");      for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key)) continue; if (ImGui::IsKeyReleased(key)) { ImGui::SameLine(); ImGui::Text("\"%s\" %d", ImGui::GetKeyName(key), key); } }
				ImGui::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
				ImGui::Text("Chars queue:");        for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.

				// Draw an arbitrary US keyboard layout to visualize translated keys
				{
					const ImVec2 key_size = ImVec2(35.0f, 35.0f);
					const float  key_rounding = 3.0f;
					const ImVec2 key_face_size = ImVec2(25.0f, 25.0f);
					const ImVec2 key_face_pos = ImVec2(5.0f, 3.0f);
					const float  key_face_rounding = 2.0f;
					const ImVec2 key_label_pos = ImVec2(7.0f, 4.0f);
					const ImVec2 key_step = ImVec2(key_size.x - 1.0f, key_size.y - 1.0f);
					const float  key_row_offset = 9.0f;

					ImVec2 board_min = ImGui::GetCursorScreenPos();
					ImVec2 board_max = ImVec2(board_min.x + 3 * key_step.x + 2 * key_row_offset + 10.0f, board_min.y + 3 * key_step.y + 10.0f);
					ImVec2 start_pos = ImVec2(board_min.x + 5.0f - key_step.x, board_min.y);

					struct KeyLayoutData { int Row, Col; const char* Label; ImGuiKey Key; };
					const KeyLayoutData keys_to_display[] =
					{
						{ 0, 0, "", ImGuiKey_Tab },      { 0, 1, "Q", ImGuiKey_Q }, { 0, 2, "W", ImGuiKey_W }, { 0, 3, "E", ImGuiKey_E }, { 0, 4, "R", ImGuiKey_R },
						{ 1, 0, "", ImGuiKey_CapsLock }, { 1, 1, "A", ImGuiKey_A }, { 1, 2, "S", ImGuiKey_S }, { 1, 3, "D", ImGuiKey_D }, { 1, 4, "F", ImGuiKey_F },
						{ 2, 0, "", ImGuiKey_LeftShift },{ 2, 1, "Z", ImGuiKey_Z }, { 2, 2, "X", ImGuiKey_X }, { 2, 3, "C", ImGuiKey_C }, { 2, 4, "V", ImGuiKey_V }
					};

					// Elements rendered manually via ImDrawList API are not clipped automatically.
					// While not strictly necessary, here IsItemVisible() is used to avoid rendering these shapes when they are out of view.
					ImGui::Dummy(ImVec2(board_max.x - board_min.x, board_max.y - board_min.y));
					if (ImGui::IsItemVisible())
					{
						ImDrawList* draw_list = ImGui::GetWindowDrawList();
						draw_list->PushClipRect(board_min, board_max, true);
						for (int n = 0; n < IM_ARRAYSIZE(keys_to_display); n++)
						{
							const KeyLayoutData* key_data = &keys_to_display[n];
							ImVec2 key_min = ImVec2(start_pos.x + key_data->Col * key_step.x + key_data->Row * key_row_offset, start_pos.y + key_data->Row * key_step.y);
							ImVec2 key_max = ImVec2(key_min.x + key_size.x, key_min.y + key_size.y);
							draw_list->AddRectFilled(key_min, key_max, IM_COL32(204, 204, 204, 255), key_rounding);
							draw_list->AddRect(key_min, key_max, IM_COL32(24, 24, 24, 255), key_rounding);
							ImVec2 face_min = ImVec2(key_min.x + key_face_pos.x, key_min.y + key_face_pos.y);
							ImVec2 face_max = ImVec2(face_min.x + key_face_size.x, face_min.y + key_face_size.y);
							draw_list->AddRect(face_min, face_max, IM_COL32(193, 193, 193, 255), key_face_rounding, ImDrawFlags_None, 2.0f);
							draw_list->AddRectFilled(face_min, face_max, IM_COL32(252, 252, 252, 255), key_face_rounding);
							ImVec2 label_min = ImVec2(key_min.x + key_label_pos.x, key_min.y + key_label_pos.y);
							draw_list->AddText(label_min, IM_COL32(64, 64, 64, 255), key_data->Label);
							if (ImGui::IsKeyDown(key_data->Key))
								draw_list->AddRectFilled(key_min, key_max, IM_COL32(255, 0, 0, 128), key_rounding);
						}
						draw_list->PopClipRect();
					}
				}
				ImGui::TreePop();
			}

		}
		ImGui::End();
	}

	//WINDOWS 
	ImGuiIO& io = ImGui::GetIO();
	if (App->ui->hierarchy)
	{
		
		selectedGameObjects = App->engineSystem->GetselectedGameObjects();
		
		ImGui::Begin("Hierarchy", &App->ui->hierarchy);
		windowSize = ImVec2(App->ui->screenX / 5.5f, App->ui->screenY - App->ui->screenY / 4 - 17.0);
		ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) * 0.0f, 18.9f));
		ImGui::SetWindowSize(windowSize);

		Scene* currentScene = App->engineSystem->GetCurrentScene();

		if (!currentScene->gameObjects.empty())
		{

			static bool alignLabelWithCurrentXPosition = false;

			if (alignLabelWithCurrentXPosition)
				ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

			
			for (GameObject* go : currentScene->gameObjects)
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

				if (go->parent == nullptr) DisplayTree(go, flags);
			}
			
			if (alignLabelWithCurrentXPosition)
				ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		}
		
		ImGui::End();
	}

	if (App->ui->inspector)
	{
		

		/*WindowGameObjectInfo windowGameObjectInfo = gameObject->windowGameObjectInfo;*/
		ImGui::Begin("Inspector", &App->ui->inspector);
		windowSize = ImVec2(App->ui->screenX / 5.5f, App->ui->screenY - App->ui->screenY / 4 - 17.0);
		ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) + 0.80f , 18.9f));
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

		if (!selectedGameObjects.empty())
		{
			GameObject* editorObject = selectedGameObjects[0];

			/*if (selectedGameObjects.size() > 1)
			{
				editorObject = ghostObject;
			
			}*/

			if (ImGui::CollapsingHeader("Information"))
			{

				ImGui::Text("Name:");
				ImGui::SameLine();
				ImGui::InputText("##Name", &editorObject->name);
				ImGui::Checkbox("Active", &editorObject->enabled);
			}
			// Current game object (the one we have selected at the moment)
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


							aiMatrix4x4* tempMat = new aiMatrix4x4;

							aiVector3D* tempScale = new aiVector3D(1, 1, 1);

							aiQuaternion* tempRotationQuat = new aiQuaternion(rotationQuat);

							aiVector3D* tempPosition = new aiVector3D(0,0,0);
							

							aiMatrix4FromScalingQuaternionPosition(tempMat, tempScale, tempRotationQuat, tempPosition);

							
							mat4x4 resMat = IdentityMatrix;

							resMat[0] = (float)tempMat->a1;
							resMat[1] = (float)tempMat->a2;
							resMat[2] = (float)tempMat->a3;
							resMat[3] = (float)tempMat->a4;
							
							resMat[4] = (float)tempMat->b1;
							resMat[5] = (float)tempMat->b2;
							resMat[6] = (float)tempMat->b3;
							resMat[7] = (float)tempMat->b4;
							
							resMat[8] = (float)tempMat-> c1;
							resMat[9] = (float)tempMat-> c2;
							resMat[10] = (float)tempMat->c3;
							resMat[11] = (float)tempMat->c4;
							
							resMat[12] = (float)tempMat->d1;
							resMat[13] = (float)tempMat->d2;
							resMat[14] = (float)tempMat->d3;
							resMat[15] = (float)tempMat->d4;

							resMat.transpose();

							if (editingModeWorld)
							{
								editorObject->transform->rotationLocal = resMat;

							}
							else
							{
								editorObject->transform->rotationLocal = resMat;



							}
							editorObject->transform->ApplyTransformations();

							delete tempMat;
							delete tempScale;
							delete tempRotationQuat;
							delete tempPosition;

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
							
							if (editingModeWorld)
							{
								editorObject->transform->scalingLocal.scale(/*editorObject->transform->GetScale().x +*/ newScale.x, /*editorObject->transform->GetScale().y +*/  newScale.y, /*editorObject->transform->GetScale().z +*/ newScale.z);
							}
							else
							{
								editorObject->transform->scalingLocal.scale(/*editorObject->transform->GetScale().x +*/ newScale.x, /*editorObject->transform->GetScale().y +*/  newScale.y, /*editorObject->transform->GetScale().z +*/ newScale.z);


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


						float3 debugRot = editorObject->transform->rotationEulerWorld;
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
						ImGui::Text(std::to_string(debugMat3[15]).c_str());


						


					}
				}
				break;
				case GOC_Type::GOC_CAMERA:
				{
					GOC_Camera* camera = (GOC_Camera*)component;
					
					if (ImGui::CollapsingHeader("Camera"))
					{
						const char* camType = frustum.type == PerspectiveFrustum ? "Perspective" : "Orthographic";
						ImGui::Text("Camera type: ", camType);
						ImGui::DragFloat("Far plane distance", &frustum.farPlaneDistance, 10, frustum.nearPlaneDistance, 2000.0f);
						ImGui::DragFloat("Near plane distance", &frustum.nearPlaneDistance, 1, 0.1, frustum.farPlaneDistance);

						float fov = frustum.verticalFov * RADTODEG;
						if (ImGui::DragFloat("FOV", &fov, 1, 55, 120))
						{
							frustum.verticalFov = fov * DEGTORAD;
							frustum.horizontalFov = 2.f * atan(tan(frustum.verticalFov * 0.5f) * (float(App->window->width) / App->window->height));
						}
					}
					else
					{
						ImGui::Text("Invalid camera type");
					}
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

						bool drawBBox = renderer->GetMesh().GetDrawBoundingBox();

						if (ImGui::Checkbox("Draw Bounding Box", &drawBBox))
						{
							renderer->GetMesh().SetDrawBoundingBox(&drawBBox);

						}


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
								/*char* tex_name = nullptr;
								strncpy_s(tex_name, tex.name.length() - 4, tex.name.c_str(), tex.name.length() - 4);*/

								if (std::strcmp(tex.name.c_str(), name.c_str()) == 0)
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
				}

			}

			/*for (GameObject* go : selectedGameObjects)
			{
				
				go->CopyFromGameObject(*editorObject);
					
			}*/

		}


		ImGui::End();
	}

	if (App->ui->assets)
	{
		ImGui::Begin("Assets", &App->ui->assets);

		ImGui::End();
	}
	
	if (App->ui->showOutput)
	{
		ImGui::Begin("Output", &App->ui->showOutput);
		windowSize = ImVec2(App->ui->screenX, App->ui->screenY / 4);
		ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) * 0.5f, (io.DisplaySize.y - windowSize.y)));
		ImGui::SetNextWindowSize(windowSize);
		App->ui->PrintOutputList();

		ImGui::End();
	}

	//PRIMITIVES
	if (App->ui->createEmptyObject)
	{
		App->engineSystem->GetCurrentScene()->CreateNewGameObject();

		App->ui->createEmptyObject = false;
	}
	if (App->ui->createCube)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cube.fbx");

		App->ui->createCube = false;
	}
	if (App->ui->createSphere)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Sphere.fbx");

		App->ui->createSphere = false;
	}
	if (App->ui->createCapsule)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Capsule.fbx");

		App->ui->createCapsule = false;
	}
	if (App->ui->createCylinder)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cylinder.fbx");

		App->ui->createCylinder = false;
	}
	if (App->ui->createPyramid)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Pyramid.fbx");

		App->ui->createPyramid = false;
	}
	if (App->ui->createCone)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Cone.fbx");

		App->ui->createCone = false;
	}
	if (App->ui->createPlane)
	{
		App->engineSystem->LoadFromPath((char*)"Assets/Primitives/Plane.fbx");

		App->ui->createPlane = false;
	}

	if (App->ui->cleanPrimitives)
	{
		App->ui->createCube = false;
		App->ui->createSphere = false;
		App->ui->createCapsule = false;
		App->ui->createCylinder = false;
		App->ui->createPlane = false;

		App->ui->cleanPrimitives = false;
	}

	//App->ui->AppendToOutput(DEBUG_LOG("selected size: %i", selectedGameObjects.size()));
	return UPDATE_CONTINUE;
}

// Hierarchy
void UIFunctions::DisplayTree(GameObject* go, int flags)
{
	flags |= ImGuiTreeNodeFlags_Leaf;

	DragAndDrop(go);

	Scene* currentScene = App->engineSystem->GetCurrentScene();

	//if (go->parent != nullptr)
	//{
	//	ImGui::Dummy(ImVec2(5, 0));
	//	ImGui::SameLine();
	//}
	if (ImGui::TreeNode(go->name.c_str()))
	{
		//for (GameObject* sceneGo : App->engineSystem->GetCurrentScene()->gameObjects)
		//{
		//	sceneGo->selected = false;
		//}
		for (int i = 0; i < go->GetChildren().size(); i++)
		{
			DisplayTree(go->GetChildren()[i], flags);
		}

		selectedGameObjects.push_back(go);
			
		go->selected = true;

		
		ImGui::Dummy(ImVec2(8, 0));
		ImGui::SameLine();
		if (ImGui::MenuItem("Create Child", "", false, false))
		{
			//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
			//	{

			//		if (go->GetID() == go->selected && go->GetID() != -1)
			//		{
			//			/*go->Delete();*/
			//			go->selected = 0;

			//		}

			//	}
		}

		ImGui::Dummy(ImVec2(0, 0));
		ImGui::SameLine();
		if (ImGui::MenuItem("Delete", "", false, false))
		{
		//	for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
		//	{

		//		if (go->GetID() == go->selected && go->GetID() != -1)
		//		{
		//			/*go->Delete();*/
		//			go->selected = 0;

		//		}

		//	}
		}
		ImGui::TreePop();
		
	}
	else
	{
		go->selected = false;
	}
}
	


void UIFunctions::DragAndDrop(GameObject* go)
{
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("Hierarchy", go, sizeof(GameObject));
		selectedGameObject = go;
		ImGui::Text(go->name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Hierarchy");
		if (payload != nullptr)
		{
			if (selectedGameObject != nullptr)
			{
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly))
				{
					destinationGameObject = go;
					destinationGameObject->AttachChild(selectedGameObject);
					selectedGameObject = nullptr;
					destinationGameObject = nullptr;
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}

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

