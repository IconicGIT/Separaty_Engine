#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
//#include "ModuleRenderer3D.h"
//#include "ModuleWindow.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_internal.h"
#include "External/Imgui/imgui.h"
#include "imgui.h"

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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleUI::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	ImGui::ShowDemoWindow();
	ImGui::Begin("Separaty Engine");
	ImGui::SetWindowSize({400, 400}, 0);
	ImGui::Text("Example");

	if (ImGui::Button("Example2", { 250, 150 }))
	{
		exit(0);
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}