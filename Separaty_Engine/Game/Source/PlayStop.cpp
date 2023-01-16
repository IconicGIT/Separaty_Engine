#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "PlayStop.h"

#include <ctime>


//PLAY & STOP WINDOW

PlayStop::PlayStop()
{
	name = "PlayStop";
}


PlayStop::~PlayStop()
{

}

update_status PlayStop::Update(float dt)
{
	ImVec2 windowSize = ImVec2(0, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (App->ui->playStop)
	{
		ImGui::Begin("PlayStop", &App->ui->playStop, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);


		if (play)
		{
			if (!pause)
			{
				time += dt *timeSpeed;
			}

			windowSize = ImVec2(410, 70.5);
			ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) / 2, 24));
			ImGui::SetWindowSize(windowSize);
			
			if (ImGui::Button("Stop", { 50,25 }))
			{
				play = false;

				time = 0;

				App->ui->uiFunctions->playStopIndividualWindow->time = 0;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Pause", { 50,25 }))
			{
				pause = !pause;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Tick", { 50,25 }))
			{
				time += dt *timeSpeed;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			/*float timeSpeed = App->time->GetGameScale();*/
			ImGui::PushItemWidth(50.0f);
			ImGui::SetCursorPos({ ImGui::GetCursorPosX(), 10 });
			if (ImGui::SliderFloat("Game Time: ", &timeSpeed, 0.0f, 2.0f, "%0.2f"))
			{
				//App->time->SetScaleGame(timeSpeed); 
			}
			ImGui::SameLine();

			std::string gameCount = std::to_string(time /*&App->time->GetGameTimer()*/);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", gameCount.data());

			if (ImGui::Checkbox("Use Camera  ", &App->ui->uiFunctions->inspectorWindow->useCamInPlay))
			{
				int a = 0;
			}
			ImGui::SameLine();
			if (ImGui::Button("Use Camera ", { 200, 25 }))
			{
				App->ui->uiFunctions->inspectorWindow->useCamInPlay != App->ui->uiFunctions->inspectorWindow->useCamInPlay;
			}
			
			ImGui::SameLine();
		}	
		else
		{
			windowSize = ImVec2(198.5, 41.5);
			ImGui::SetWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) / 2, 24));
			ImGui::SetWindowSize(windowSize);

			if (ImGui::Button("Play", { 50,25 }))
			{
				play = true;
				pause = false;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Pause", { 50, 25 }))
			{
				pause = false;
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			if (ImGui::Button("Tick", { 50,25 }))
			{
				time += dt *timeSpeed;
			}

			gameTime = 0.0f;
		}		

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

//std::string PlayStop::GetTimeAsString()
//{
//	std::string time_string = std::to_string(hours) + "h " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
//
//	return time_string;
//}