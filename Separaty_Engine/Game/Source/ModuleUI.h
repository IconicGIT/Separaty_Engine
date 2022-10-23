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
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;


	bool closeButton = false;
	bool openAbout = false;

	bool showApplicationData = false;
	bool showPreferences = false;
	bool showOutput = true;
	std::vector<char*> outputList;

	//PRIMITIVEs

	bool createCube = false;
	bool createSphere = false;
	bool createCapsule = false;
	bool createCylinder = false;
	bool createPlane = false;

	bool cleanPrimitives = false;

	void AppendToOutput(char* DEBUG_LOG)
	{
		char* text = new char[4096];
		strncpy_s(text, 4096, DEBUG_LOG, strlen(DEBUG_LOG));

		std::vector<char*>::iterator firstPlace = outputList.begin();
		outputList.insert(firstPlace, text);
	}

	char inputs[20];
	/*GameObject* gameObject;*/

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
