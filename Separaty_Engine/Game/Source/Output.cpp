#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Output.h"


//OUTPUT WINDOW

Output::Output()
{
	name = "Output";
}


Output::~Output()
{

}

update_status Output::Update(float dt)
{
	ImVec2 windowSize = ImVec2(0, 0);

	ImGuiIO& io = ImGui::GetIO();

	if (App->ui->showOutput)
	{
		ImGui::Begin("Output", &App->ui->showOutput, ImGuiWindowFlags_NoMove);
		windowSize = ImVec2(App->ui->screenX / 1.221, App->ui->screenY / 4);
		ImGui::SetNextWindowPos(ImVec2(0, (io.DisplaySize.y - windowSize.y) + 0.80f));
		ImGui::SetNextWindowSize(windowSize);
		App->ui->PrintOutputList();

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}
