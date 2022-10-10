#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"



#include <string> 

#include "Glew/include/glew.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//#include "opengl_shaders.h"

ModuleUI::ModuleUI(bool start_enabled) : Module(start_enabled)
{

}

ModuleUI::~ModuleUI()
{}


bool ModuleUI::Start()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGuiStyle & style = ImGui::GetStyle();
	
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleUI::Update(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();
	ImGui::Begin("Separaty Engine");
	ImGui::SetWindowSize({ 400, 400 }, 0);

	/*if (ImGui::Button("Example2", { 250, 150 }))
	{
		exit(0);
	}*/

	/////////////////////
	if (ImGui::BeginMainMenuBar())
	{
		//FILE 
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene" , "CTRL + N"))
			{

			}
			if (ImGui::MenuItem("Open Scene", "CTRL + O"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Save", "CTRL + S"))
			{

			}
			if (ImGui::MenuItem("Save As", "CTRL + SHIFT + S"))
			{

			}

			if (ImGui::MenuItem("Load", "CTRL + L"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("New Project"))
			{

			}
			if (ImGui::MenuItem("Open Project"))
			{

			}
			if (ImGui::MenuItem("Save Project"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}


		// EDIT
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL + Z"))
			{

			}
			if (ImGui::MenuItem("Redo", "CTRL + Y", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Select All", "SHIFT + A"))
			{

			}
			if (ImGui::MenuItem("Deselect All", "SHIFT + D"))
			{

			}
			/*if (ImGui::MenuItem("Invert Selection", "CTRL + I"))
			{

			}*/
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL + X"))
			{

			}
			if (ImGui::MenuItem("Copy", "CTRL + C"))
			{

			}
			if (ImGui::MenuItem("Paste", "CTRL + V"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Duplicate", "CTRL + D"))
			{

			}
			if (ImGui::MenuItem("Rename", "SHIFT + R"))
			{

			}
			if (ImGui::MenuItem("Delete", "SUPR"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Frame Selected", "F"))
			{

			}
			if (ImGui::MenuItem("Lock View to Selected", "SHIFT + F"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Project Settings..."))
			{

			}
			if (ImGui::MenuItem("Preferences..."))
			{
				showPreferences = !showPreferences;
				
			}
			if (ImGui::MenuItem("Show Application Data"))
			{
				showApplicationData = !showApplicationData;
			}
			if (ImGui::MenuItem("Show Output"))
			{
				showOutput = !showOutput;
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Controls"))
			{

			}
			ImGui::EndMenu();
		}

		//Game Object
		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::TreeNode("Create 3D Object"))
			{
				if (ImGui::MenuItem("Cube"))
				{

				}
				if (ImGui::MenuItem("Sphere"))
				{

				}
				if (ImGui::MenuItem("Capsule"))
				{

				}
				if (ImGui::MenuItem("Cylinder"))
				{

				}
				if (ImGui::MenuItem("Plane"))
				{

				}
				ImGui::TreePop();

			}
			ImGui::Separator();
			if (ImGui::TreeNode("Effects"))
			{
				if (ImGui::MenuItem("Particles"))
				{

				}

				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Light"))
			{
				if (ImGui::MenuItem("Directional Light"))
				{

				}
				if (ImGui::MenuItem("Point Light"))
				{

				}
				if (ImGui::MenuItem("Spotlight"))
				{

				}
				if (ImGui::MenuItem("Area Light"))
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Audio"))
			{
				if (ImGui::MenuItem("Audio Source"))
				{

				}
				if (ImGui::MenuItem("Audio Reverb Zone"))
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Camera"))
			{

			}
			ImGui::EndMenu();
		}

		//VIEW
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::TreeNode("Render Options"))
			{

				if (ImGui::Checkbox("GL_AmbientOclussion", &App->window->fullScreen)) // Funcion de prueba
				{

				}
				if (ImGui::Checkbox("GL_Color_material", &App->window->fullScreen)) // Funcion de prueba
				{

				}
				if (ImGui::Checkbox("GL_Cull_face", &App->window->fullScreen)) // Funcion de prueba
				{


				}
				if (ImGui::Checkbox("GL_Depth_test", &App->window->fullScreen)) // Funcion de prueba
				{

				}
				if (ImGui::Checkbox("GL_Front", &App->window->fullScreen)) // Funcion de prueba
				{

				}
				if (ImGui::Checkbox("GL_Lightning", &App->window->fullScreen)) // Funcion de prueba
				{


				}
				if (ImGui::Checkbox("Wireframe Mode", &App->window->fullScreen)) // Funcion de prueba
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			ImGui::EndMenu();
		}

		//WINDOWS
		if (ImGui::BeginMenu("Window")) //PUEDE IR PERFECTAMENTE EN EL WINDOW DE ABAJO
		{
			if (ImGui::TreeNode("Brightness"))
			{
				ImGui::SliderFloat("Brightness", &App->window->brightness, 0.001f, 1.000f); //NO FUNCIONA
				//App->window->UpdateBrightness();
				ImGui::TreePop();

			}
			ImGui::Separator();
			if (ImGui::TreeNode("Windows Size"))
			{
				if (ImGui::Checkbox("Full Screen", &App->window->fullScreen)) //FUNCIONA
				{
					App->window->SetFullscreen(App->window->fullScreen);
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Full Desktop", &App->window->fullDesktop)) //FUNCIONA
				{
					App->window->SetFullscreen(App->window->fullDesktop);
				}
				ImGui::Separator();
				if (ImGui::Checkbox("Resizable  ", &App->window->resizable)) //FUNCIONA
				{
					App->window->SetResizable(App->window->resizable);
				}			
				ImGui::SliderInt("Width", &App->window->width, 720, 1920);	 //FUNCIONA
				ImGui::SliderInt("Height", &App->window->height, 480, 1080); //FUNCIONA
				//App->window->UpdateWindowSize();


				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Vsync"))
			{
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "Refresh rate: %d", App->window->maxFPS);
				ImGui::SameLine();
				if (ImGui::Checkbox("Vsync", &App->window->vsync))
				{
					App->window->SetVsync(App->window->vsync);
				}
				App->window->FPSGraph(dt, 60);
				App->window->MSGraph(dt, 60);

				ImGui::TreePop();
			}
			ImGui::Separator();
			/*if (ImGui::Button("Save", ImVec2(60, 25)))
			{
				App->Save();
				WASHI_LOG("Saving");
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Click to save your preferences!");
			}*/

			ImGui::EndMenu();
		}

		//HELP
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::TreeNode("About us"))
			{
				ImGui::Text("SEPARATY ENGINE");
				ImGui::Separator();
				ImGui::Text("An engine that without hesitation, will be BETTER THAN UNITY!");
				ImGui::Separator();
				ImGui::Text("By Gerard Martinez & Brandon Arandia");
				ImGui::NewLine();

				ImGui::Text("Take a look at our github:");
				if (ImGui::Button("Github"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");  
				}
				ImGui::NewLine();

				ImGui::Text("Visit github page for detailed information regarding code and functionalities:");
				if (ImGui::Button("Github Web Page"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}
				ImGui::NewLine();

				ImGui::Text("Download latest versions of the Engine here:");
				if (ImGui::Button("Latest versions"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}
				/*if (ImGui::Button("l"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}*/
				ImGui::NewLine();
				ImGui::Separator();
				//ImGui::NewLine();

				ImGui::Text("3rd parties libraries used:");
				//LIBRERIAS UTILIZADAS DURANTE EL PROYECTO (faltan)
				ImGui::BulletText("SDL 2.0.4");
				ImGui::BulletText("MathGeoLib 1.5");
				ImGui::BulletText("Json 1.2.1");
				ImGui::BulletText("ImGui 1.89");
				ImGui::BulletText("Glew 2.2.0");
				ImGui::BulletText("OpenGL 2.0");






				/////////////////////////

				ImGui::NewLine();
				ImGui::Separator();
				//ImGui::NewLine();
				ImGui::Text("MIT License");
				ImGui::NewLine();
				ImGui::Text("Copyright (c) 2012 - 2021 Krzysztof Gabis");
				ImGui::NewLine();
				ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a");
				ImGui::Text("copy of this software and associated documentation files(the 'Software'),");
				ImGui::Text("to dealin the Software without restriction, including without limitation");
				ImGui::Text("the rights to use, copy, modify, merge, publish, distribute, sublicense,");
				ImGui::Text("and /or sell copies of the Software, and to permit persons to whom the");
				ImGui::Text("Software is furnished to do so, subject to the following conditions:");
				ImGui::NewLine();
				ImGui::Text("The above copyright notice and this permission notice shall be included");
				ImGui::Text("in all copies or substantial portions of the Software.");
				ImGui::NewLine();
				ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
				ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
				ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
				ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
				ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
				ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN");
				ImGui::Text("THE SOFTWARE.");

				
				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Separaty Manual"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");   
			}
			
			if (ImGui::MenuItem("Engine Uses & Examples"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Make Any Comment"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}

			if (ImGui::MenuItem("Report Bugs"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
		
			ImGui::EndMenu();
		}

		
		ImGui::EndMainMenuBar();
	}
	//////////////////////


	//VENTANAS EMERGENTES DE LOS DIFERENTES MENUS 

	//EDIT
	// 
		//Preferences
	if (showPreferences)
	{
		ImGui::Begin("Preferences...", &showPreferences);

		if (ImGui::TreeNode("Style"))
		{
			ImGui::ShowStyleEditor();
			ImGui::TreePop();
			ImGui::Separator();
		}

		ImGui::End();
	}
		//APP DATA
	if (showApplicationData)
	{
		ImGui::Begin("Show Application Data", &showApplicationData);

		// Application 
		if (ImGui::CollapsingHeader("Application"))
		{
			//AppNameDisplay
			sprintf_s(inputs, 20, TITLE);
			ImGui::InputText("App Name", inputs, 20);
			//OrganizationNameDisplay (Citm)
			sprintf_s(inputs, 20, ORGANITZATION);
			ImGui::InputText("Organization", inputs, 20);
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

	if (showOutput)
	{
		ImGui::Begin("Output", &showOutput);

		PrintOutputList();

		ImGui::End();
	}

	ImGui::End();
	ImGui::Render();
	//ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	for (char* listElement : outputList)
	{
		delete listElement;
	}

	return true;
}