#pragma once
#include "Module.h"
#include "Globals.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"

class ModuleUI : public Module
{
public:
	ModuleUI(bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	bool closeButton = false;
	bool openAbout = false;

	bool showApplicationData = false;
	bool showPreferences = false;
	bool showOutput = false;
	std::vector<char*> outputList;

	void AppendToOutput(char* DEBUG_LOG)
	{
		char* text = new char[4096];
		strncpy_s(text, 4096, DEBUG_LOG, strlen(DEBUG_LOG));

		std::vector<char*>::iterator firstPlaec = outputList.begin();
		outputList.insert(firstPlaec, text);
	}

	char inputs[20];


	//TODO 9: Create an "OnCollision" method specific for this module



private:
	
	void PrintOutputList()
	{
		for (char* listElement : outputList)
		{
			ImGui::Text(listElement);
		}
	}

};
