#pragma once

#include "ModuleUI.h"
#include "Globals.h"
#include "GameObject.h"
#include "MathGeoLib/Math/Quat.h"
#include "ProjectPreferences.h"
#include "AppData.h"
#include "Hierarchy.h"
#include "Inspector.h"
#include "Assets.h"
#include "Output.h"
#include "PlayStop.h"

class EngineSystem;
class GameObject;

//class ModuleUI;
class Module;

class UIFunctions : public Module
{
public:

	UIFunctions();

	~UIFunctions();

	bool Start();
	update_status Update(float dt) override;

	Preferences* showPreferences;
	AppData* showApplicationData;
	Hierarchy* hierarchyWindow;
	Inspector* inspectorWindow;
	Assets* assetsWindow;
	Output* outputWindow;
	PlayStop* playStopWindow;

	std::vector<GameObject*> selectedGameObjects;

	void EraseFromSelectedGoList(GameObject* toErase);

private:

	EngineSystem* engineSystem;

	GameObject* ghostObject = nullptr;

	//GameObject* gameObject = nullptr;

	/*true = editing in WORLD mode
	false = editing in LOCAL mode*/

};
