#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
//#include "ModuleRenderer3D.h"
//#include "ModuleWindow.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"



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
	ImGui::Text("Example");

	/*if (ImGui::Button("Example2", { 250, 150 }))
	{
		exit(0);
	}*/

	/////////////////////
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene"))
			{

			}
			if (ImGui::MenuItem("Open Scene"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Save"))
			{

			}
			if (ImGui::MenuItem("Load"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("1"))
			{

			}
			if (ImGui::MenuItem("1"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Close"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
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

			}
			if (ImGui::MenuItem("Show Application Data"))
			{
				//Crear Ventana con todo 
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Controls"))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{

			if (ImGui::Checkbox("Fullscreen", &fullScreen))
			{
				App->window->SetFullscreen(fullScreen);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Vsync", &Vsync))
			{
				App->window->SetVsync(Vsync);
			}
			if (ImGui::Checkbox("Resizable", &resizable))
			{
				App->window->SetResizable(resizable);
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{


			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About us"))
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
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");   //TEST PARA VER CUAL QUEDA MEJOR
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
			
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	//////////////////////

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

	return true;
}