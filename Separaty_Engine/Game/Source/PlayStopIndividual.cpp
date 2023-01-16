#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "PlayStopIndividual.h"

#include <iostream>
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
	ImVec2 windowSize = ImVec2(0, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (!App->ui->uiFunctions->playStopWindow->play)
	{
		if (App->ui->playStopIndividual)
		{
			ImGui::Begin("PlayStopIndividual", &App->ui->playStopIndividual, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);

			if (play)
			{
				if (!pause)
				{
					time += dt *timeSpeed;
				}

				windowSize = ImVec2(198, 68.5);
				ImGui::SetWindowSize(windowSize);

				if (ImGui::Button(" Stop ", { 50,25 }))
				{
					play = false;

					time = 0;
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(0, 0));
				ImGui::SameLine();

				if (ImGui::Button(" Pause ", { 50,25 }))
				{
					pause = !pause;

				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(0, 0));
				ImGui::SameLine();

				if (ImGui::Button(" Tick ", { 50,25 }))
				{
					time += dt *timeSpeed;
				}
				ImGui::Dummy(ImVec2(0, 1));

				ImGui::Text("Game Time:");
				ImGui::SameLine();
				ImGui::Text("%.3f", time, 0.0f, 2.0f, "%0.2f");
				
				ImGui::SameLine();

				ImGui::PushItemWidth(50.0f);
				if (ImGui::SliderFloat("##100", &timeSpeed, 0.0f, 2.0f, "%0.2f"))
				{
					//App->time->SetScaleGame(timeSpeed); 
				}
				ImGui::PopItemWidth();
			}
			else
			{
				windowSize = ImVec2(198, 41.5);
				ImGui::SetWindowSize(windowSize);

				if (ImGui::Button(" Play ", { 50,25 }))
				{
					play = true;
					pause = false;
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(0, 0));
				ImGui::SameLine();

				if (ImGui::Button(" Pause ", { 50, 25 }))
				{
					pause = false;
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(0, 0));
				ImGui::SameLine();

				if (ImGui::Button(" Tick ", { 50,25 }))
				{
					time += dt *timeSpeed;
				}
				ImGui::Dummy(ImVec2(0, 1));

				ImGui::Text("Game Time:");
				ImGui::SameLine();
				ImGui::Text("%.3f", time, 0.0f, 2.0f, "%0.2f");

				ImGui::SameLine();

				ImGui::PushItemWidth(50.0f);
				if (ImGui::SliderFloat("##100", &timeSpeed, 0.0f, 2.0f, "%0.2f"))
				{
					//App->time->SetScaleGame(timeSpeed); 
				}
				ImGui::PopItemWidth();

			}

			ImGui::End();
		}
	}
	

	return UPDATE_CONTINUE;
}

