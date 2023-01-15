#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "PlayStopIndividual.h"

#include <ctime>


//PLAY & STOP WINDOW

PlayStopIndividual::PlayStopIndividual()
{
	name = "PlayStopIndividual";
}


PlayStopIndividual::~PlayStopIndividual()
{

}

update_status PlayStopIndividual::Update(float dt)
{
	ImVec2 windowSize = ImVec2(100, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (App->ui->playStopIndividual)
	{
		ImGui::Begin("PlayStopIndividual", &App->ui->playStopIndividual, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);


		if (play)
		{
			if (ImGui::Button("Stop ", { 50,25 }))
			{
				play = false;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Pause ", { 50,25 }))
			{
				pause != pause;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Tick ", { 50,25 }))
			{
				/*dt++;*/
			}
			ImGui::Dummy(ImVec2(0, 0));

			ImGui::Text("Game Time:");
			ImGui::SameLine();
			ImGui::Text("%.3f", &timeSpeed, 0.0f, 2.0f, "%0.2f");
			/*float timeSpeed = App->time->GetGameScale();*/
		

		}
		else
		{

			if (ImGui::Button("Play ", { 50,25 }))
			{
				play = true;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Pause ", { 50, 25 }))
			{

			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Tick ", { 50,25 }))
			{

			}
			ImGui::Dummy(ImVec2(0, 0));

			ImGui::Text("Game Time:");
			ImGui::SameLine();
			ImGui::Text("%.3f", &timeSpeed, 0.0f, 2.0f, "%0.2f");

		}

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

