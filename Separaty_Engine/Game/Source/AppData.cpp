#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "AppData.h"


//APP DATA

AppData::AppData()
{
	name = "AppData";
}


AppData::~AppData()
{

}

update_status AppData::Update(float dt)
{

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

			float maxFpsAvaiable = 1000;
			//MaxFPSSlider
			ImGui::SliderInt("Max FPS", &App->window->maxFPS, 6, maxFpsAvaiable);
			//LimitFramerateText Limit Framereate: %d
			ImGui::Text("Limit Framerate: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", App->window->maxFPS);
			//FPSGraph
			App->window->FPSGraph(dt, 100, maxFpsAvaiable + 50);

			//MillisecondsGraph - delta time Graph
			App->window->MSGraph(dt, 0.1f, maxFpsAvaiable + 50);

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

	return UPDATE_CONTINUE;
}
