#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"




ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	DEBUG_LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	plane.SetNormal(0, 1, 0);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	DEBUG_LOG("Unloading Intro scene");

	for (int n = 0; n < primitives.size(); n++)
	{
		delete primitives[n];
	}
	primitives.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	plane.Render();
	cube.Render();
	//sphere.Render();
	//cil.Render();

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		plane.SetExtension(10);
		sphere.SetRadius(1);
		sphere.SetColumns(5);
		//sphere.SetRows(5);
		cil.SetColumns(10);
	}
	else
	{
		plane.SetExtension(200);
		sphere.SetRadius(1);

		sphere.SetColumns(25);
		sphere.SetRows(25);
		cil.SetColumns(30);

	}

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
	{
		App->ui->AppendToOutput(DEBUG_LOG("text"));
	}

	if (App->debug == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			//TODO 3: Create a "new" sphere, and add it to the "primitives" DynArray

			//TODO 9: Push ModuleSceneIntro to the sphere collision listeners
		}
	}


	//TODO 3: Nothing to do here. But it's good to know where all primitives are being updated
	//for (uint n = 0; n < primitives.Count(); n++)
	//{
	//	primitives[n]->Update();
	//}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//TODO 3: Nothing to do here. But it's good to know where all primitives are being rendered
	//for (uint n = 0; n < primitives.Count(); n++)
	//{
	//	primitives[n]->Render();
	//}

	return UPDATE_CONTINUE;
}

//TODO 9: And change the color of the colliding bodies, so we can visualize it working!