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

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


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
			if (ImGui::Button("New Scene"))
			{

			}
			if (ImGui::Button("Open Scene"))
			{

			}
			ImGui::Separator();
			if (ImGui::Button("Save"))
			{

			}
			if (ImGui::Button(""))
			{

			}
			ImGui::Separator();
			if (ImGui::Button(""))
			{

			}
			if (ImGui::Button(""))
			{

			}
			ImGui::Separator();
			if (ImGui::Button("Close"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z"))
			{

			}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X"))
			{

			}
			if (ImGui::MenuItem("Copy", "CTRL+C"))
			{

			}
			if (ImGui::MenuItem("Paste", "CTRL+V"))
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
			ImGui::Text("Separaty Engine");

			ImGui::Separator();

			if (ImGui::Button("Github"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
			if (ImGui::Button("Github Web Page"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
			if (ImGui::Button("Download latest versions"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
			if (ImGui::Button(""))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}

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