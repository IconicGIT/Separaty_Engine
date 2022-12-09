#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "ProjectPreferences.h"


//PROJECT PREFERENCES

Preferences::Preferences()
{
	name = "Preferences";
}


Preferences::~Preferences()
{

}

update_status Preferences::Update(float dt)
{

	if (App->ui->showPreferences)
	{
		ImGui::Begin("Preferences...", &App->ui->showPreferences);

		if (ImGui::TreeNode("Style"))
		{
			ImGui::ShowStyleEditor();
			ImGui::TreePop();

		}
		ImGui::Separator();

		if (ImGui::TreeNode("Window Settings"))
		{
			if (ImGui::TreeNode("Brightness"))
			{
				ImGui::SliderFloat("Brightness", &App->window->brightness, 0.001f, 1.000f); 
				//App->window->UpdateBrightness();
				ImGui::TreePop();


			}
			ImGui::Separator();

			if (ImGui::TreeNode("Window Size"))
			{
				if (ImGui::Checkbox("Full Screen", &App->window->fullScreen)) 
				{
					App->window->SetFullscreen(App->window->fullScreen);
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Full Desktop", &App->window->fullDesktop)) 
				{
					App->window->SetFullscreen(App->window->fullDesktop);
				}
				ImGui::Separator();
				if (ImGui::Checkbox("Resizable  ", &App->window->resizable)) 
				{
					App->window->SetResizable(App->window->resizable);
				}
				ImGui::SliderInt("Width", &App->window->width, 720, 1920);	 
				ImGui::SliderInt("Height", &App->window->height, 480, 1080); 

				//SDL_GetWindowSize(App->window->window, &App->window->width, &App->window->height);

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
			ImGui::TreePop();
		}
		ImGui::Separator();

		if (ImGui::TreeNode("Camera Settings"))
		{
			ImGui::SliderFloat("Field of View", &App->renderer3D->fov, 1, 175.f);

			ImGui::TreePop();
		}

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}
