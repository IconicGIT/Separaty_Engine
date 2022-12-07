#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Assets.h"


//ASSETS WINDOW

Assets::Assets()
{
	name = "Assets";
}


Assets::~Assets()
{

}

update_status Assets::Update(float dt)
{
	if (App->ui->assets)
	{
		ImGui::Begin("Assets", &App->ui->assets, ImGuiWindowFlags_NoMove);

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}
