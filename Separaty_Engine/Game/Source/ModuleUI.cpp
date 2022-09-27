#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "opengl_shaders.h"




ModuleUI::ModuleUI(bool start_enabled) : Module(start_enabled)
{

}

ModuleUI::~ModuleUI()
{}


bool ModuleUI::Start()
{



	return true;
}


bool ModuleUI::CleanUp()
{



	return true;
}

// Update
update_status ModuleUI::Update(float dt)
{

	

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

