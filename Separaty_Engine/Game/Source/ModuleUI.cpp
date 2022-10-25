#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"



#include <string> 

#include "Glew/include/GL/glew.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//#include "opengl_shaders.h"

ModuleUI::ModuleUI(bool start_enabled) : Module(start_enabled)
{
	name = "User_Interface";

}

ModuleUI::~ModuleUI()
{}


bool ModuleUI::Init()
{

	uiFunctions = new UIFunctions();

	return true;
}

bool ModuleUI::Start()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGuiStyle & style = ImGui::GetStyle();
	
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	/*gameObject = new GameObject();
	gameObject->Init();
	gameObject->Start();*/

	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleUI::Update(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();
	ImGui::Begin("Separaty Engine");
	ImGui::SetWindowSize({ 400, 400 }, 0);

	/*if (ImGui::Button("Example2", { 250, 150 }))
	{
		exit(0);
	}*/

	/////////////////////
	if (ImGui::BeginMainMenuBar())
	{
		//FILE 
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene" , "CTRL + N"))
			{

			}
			if (ImGui::MenuItem("Open Scene", "CTRL + O"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Save", "CTRL + S"))
			{

				App->SaveGameRequest();
			}
			if (ImGui::MenuItem("Save As", "CTRL + SHIFT + S"))
			{

			}

			if (ImGui::MenuItem("Load", "CTRL + L"))
			{
				App->LoadGameRequest();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("New Project"))
			{

			}
			if (ImGui::MenuItem("Open Project"))
			{

			}
			if (ImGui::MenuItem("Save Project"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}


		// EDIT
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL + Z"))
			{

			}
			if (ImGui::MenuItem("Redo", "CTRL + Y", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Select All", "SHIFT + A"))
			{

			}
			if (ImGui::MenuItem("Deselect All", "SHIFT + D"))
			{

			}
			/*if (ImGui::MenuItem("Invert Selection", "CTRL + I"))
			{

			}*/
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL + X"))
			{

			}
			if (ImGui::MenuItem("Copy", "CTRL + C"))
			{

			}
			if (ImGui::MenuItem("Paste", "CTRL + V"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Duplicate", "CTRL + D"))
			{

			}
			if (ImGui::MenuItem("Rename", "SHIFT + R"))
			{

			}
			if (ImGui::MenuItem("Delete", "SUPR"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Frame Selected", "F"))
			{

			}
			if (ImGui::MenuItem("Lock View to Selected", "SHIFT + F"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Project Settings..."))
			{

			}
			if (ImGui::MenuItem("Preferences..."))
			{
				showPreferences = !showPreferences;
				
			}
			if (ImGui::MenuItem("Show Application Data"))
			{
				showApplicationData = !showApplicationData;
			}
			if (ImGui::MenuItem("Show Output"))
			{
				showOutput = !showOutput;
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Controls"))
			{

			}
			ImGui::EndMenu();
		}

		//Game Object
		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::TreeNode("Create 3D Object"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					createCube = true;
				}
				if (ImGui::MenuItem("Sphere"))
				{
					createSphere = true;
				}
				if (ImGui::MenuItem("Capsule"))
				{
					createCapsule = true;
				}
				if (ImGui::MenuItem("Cylinder"))
				{
					createCylinder = true;
				}
				if (ImGui::MenuItem("Plane"))
				{
					createPlane = true;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Clean Primitives"))
				{
					cleanPrimitives = true;
				}
				ImGui::TreePop();

			}
			ImGui::Separator();
			if (ImGui::TreeNode("Effects"))
			{
				if (ImGui::MenuItem("Particles"))
				{

				}

				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Light"))
			{
				if (ImGui::MenuItem("Directional Light"))
				{

				}
				if (ImGui::MenuItem("Point Light"))
				{

				}
				if (ImGui::MenuItem("Spotlight"))
				{

				}
				if (ImGui::MenuItem("Area Light"))
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Audio"))
			{
				if (ImGui::MenuItem("Audio Source"))
				{

				}
				if (ImGui::MenuItem("Audio Reverb Zone"))
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Camera"))
			{

			}
			ImGui::EndMenu();
		}

		//VIEW
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::TreeNode("Render Options"))
			{

				if (ImGui::Checkbox("AMBIENT OCLUSSION", &App->renderer3D->atributes.AmbientOclussion)) // Funcion de prueba
				{}

				if (ImGui::Checkbox("COLOR MATERIAL", &App->renderer3D->atributes.Color_Materials)) // Funcion de prueba
				{}

				if (ImGui::Checkbox("CULL FACE", &App->renderer3D->atributes.Cull_Face)) // Funcion de prueba
				{}

				if (ImGui::Checkbox("DEPTH TEST", &App->renderer3D->atributes.Depth_test)) // Funcion de prueba
				{}

				if (ImGui::Checkbox("FRONT", &App->renderer3D->atributes.Front)) // Funcion de prueba
				{}

				if (ImGui::Checkbox("LIGHTNING", &App->renderer3D->atributes.Lightning)) // Funcion de prueba
				{}

				if (ImGui::Checkbox("WIREFRAME", &App->renderer3D->atributes.Wireframe)) // Funcion de prueba
				{}

				ImGui::TreePop();
			}
			ImGui::Separator();
			ImGui::EndMenu();
		}

		//WINDOWS
		if (ImGui::BeginMenu("Window")) //PUEDE IR PERFECTAMENTE EN EL WINDOW DE ABAJO
		{
			if (ImGui::TreeNode("Brightness"))
			{
				ImGui::SliderFloat("Brightness", &App->window->brightness, 0.001f, 1.000f); //NO FUNCIONA
				//App->window->UpdateBrightness();
				ImGui::TreePop();

			}
			ImGui::Separator();
			if (ImGui::TreeNode("Windows Size"))
			{
				if (ImGui::Checkbox("Full Screen", &App->window->fullScreen)) //FUNCIONA
				{
					App->window->SetFullscreen(App->window->fullScreen);
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Full Desktop", &App->window->fullDesktop)) //FUNCIONA
				{
					App->window->SetFullscreen(App->window->fullDesktop);
				}
				ImGui::Separator();
				if (ImGui::Checkbox("Resizable  ", &App->window->resizable)) //FUNCIONA
				{
					App->window->SetResizable(App->window->resizable);
				}			
				ImGui::SliderInt("Width", &App->window->width, 720, 1920);	 //FUNCIONA
				ImGui::SliderInt("Height", &App->window->height, 480, 1080); //FUNCIONA
				//App->window->UpdateWindowSize();


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
			ImGui::Separator();
			/*if (ImGui::Button("Save", ImVec2(60, 25)))
			{
				App->Save();
				WASHI_LOG("Saving");
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Click to save your preferences!");
			}*/

			ImGui::EndMenu();
		}

		//HELP
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::TreeNode("About us"))
			{
				ImGui::Text("SEPARATY ENGINE");
				ImGui::Separator();
				ImGui::Text("An engine that without hesitation, will be BETTER THAN UNITY!");
				ImGui::Separator();
				ImGui::Text("By Gerard Martinez & Brandon Arandia");
				ImGui::NewLine();

				ImGui::Text("Take a look at our github:");
				if (ImGui::Button("Github"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");  
				}
				ImGui::NewLine();

				ImGui::Text("Visit github page for detailed information regarding code and functionalities:");
				if (ImGui::Button("Github Web Page"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}
				ImGui::NewLine();

				ImGui::Text("Download latest versions of the Engine here:");
				if (ImGui::Button("Latest versions"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}
				/*if (ImGui::Button("l"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}*/
				ImGui::NewLine();
				ImGui::Separator();
				//ImGui::NewLine();

				ImGui::Text("3rd parties libraries used:");
				//LIBRERIAS UTILIZADAS DURANTE EL PROYECTO (faltan)
				ImGui::BulletText("SDL 2.0.4");
				ImGui::BulletText("MathGeoLib 1.5");
				ImGui::BulletText("Json 1.2.1");
				ImGui::BulletText("ImGui 1.89");
				ImGui::BulletText("Glew 2.2.0");
				ImGui::BulletText("OpenGL 2.0");






				/////////////////////////

				ImGui::NewLine();
				ImGui::Separator();
				//ImGui::NewLine();
				ImGui::Text("MIT License");
				ImGui::NewLine();
				ImGui::Text("Copyright (c) 2012 - 2021 Krzysztof Gabis");
				ImGui::NewLine();
				ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a");
				ImGui::Text("copy of this software and associated documentation files(the 'Software'),");
				ImGui::Text("to dealin the Software without restriction, including without limitation");
				ImGui::Text("the rights to use, copy, modify, merge, publish, distribute, sublicense,");
				ImGui::Text("and /or sell copies of the Software, and to permit persons to whom the");
				ImGui::Text("Software is furnished to do so, subject to the following conditions:");
				ImGui::NewLine();
				ImGui::Text("The above copyright notice and this permission notice shall be included");
				ImGui::Text("in all copies or substantial portions of the Software.");
				ImGui::NewLine();
				ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
				ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
				ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
				ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
				ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
				ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN");
				ImGui::Text("THE SOFTWARE.");

				
				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Separaty Manual"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");   
			}
			
			if (ImGui::MenuItem("Engine Uses & Examples"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Make Any Comment"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}

			if (ImGui::MenuItem("Report Bugs"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
			}
		
			ImGui::EndMenu();
		}

		
		ImGui::EndMainMenuBar();
	}
	//////////////////////


	//WINDOWS FROM THE DIFFERENT MEUNS 

	//EDIT
	// 
		//PREFERENCES

	uiFunctions->Update(dt);

		//APP DATA
	

	if (showOutput)
	{
		ImGui::Begin("Console", &showOutput);

		PrintOutputList();

		ImGui::End();
	}

	ImGui::End();
	ImGui::Render();
	//ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//PRIMITIVES

	/*if (createCube)
	{
		gameObject->Update(dt);
		gameObject->PostUpdate(dt);
	}
	if (createSphere)
	{
		gameObject->Update(dt);
		gameObject->PostUpdate(dt);
	}
	if (createCapsule)
	{
		gameObject->Update(dt);
		gameObject->PostUpdate(dt);
	}
	if (createCylinder)
	{
		gameObject->Update(dt);
		gameObject->PostUpdate(dt);
	}
	if (createPlane)
	{
		gameObject->Update(dt);
		gameObject->PostUpdate(dt);
	}*/

	if (cleanPrimitives)
	{
		createCube = false;
		createSphere = false;
		createCapsule = false;
		createCylinder = false;
		createPlane = false;

		cleanPrimitives = false;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	for (char* listElement : outputList)
	{
		delete listElement;
	}

	return true;
}

bool  ModuleUI::SaveState(JSON_Value* file) const
{
	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), "modules.UI.name", buf);
	json_serialize_to_file(file, "Config.json");


	//json_object_dotset_number(json_object(file), "modules.Window.width", (double)width);
	//json_object_dotset_number(json_object(file), "modules.Window.height", (double)height);


	//json_serialize_to_file(file, "Config.json");

	App->ui->AppendToOutput(DEBUG_LOG("Saved UI module."));


	return true;
}

bool  ModuleUI::LoadState(JSON_Value* file)
{
	const char* n = json_object_dotget_string(json_object(file), "modules.UI.name");

	App->ui->AppendToOutput(DEBUG_LOG("%s", n));

	return true;
}