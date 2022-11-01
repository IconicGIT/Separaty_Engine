#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"

#include "Scene.h"


ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled)
{
	name = "Camera3D";

	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	DEBUG_LOG("Setting up the camera");
	bool ret = true;
	

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	DEBUG_LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{

	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0,0,0);
	float speed = 10.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 20.0f * dt;

	if(App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
	if(App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT 
	&& !(App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN))
		newPos += Z * speed;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		for (GameObject* go : App->engineSystem->GetCurrentScene()->gameObjects)
		{
			if (go->selected)
			{
				LookAt(go->transform->GetPosition());
			}
			else
			{
				LookAt(0);
			}
		}
		
	}

	Position += newPos;
	Reference += newPos;

	// Mouse motion ----------------

	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		Position -= Reference;

		if(dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if(dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if(Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
	}

	//zoomSpeed = App->camera->GetZoomSpeed();
	//App->camera->GetZoomSpeed(zoomSpeed);
	
	/*if (App->input->GetMouseZ() != 0)
	{
		Zoom();
	}*/

	if (App->input->GetMouseZ() != 0)
	{
		Zoom(zoomSpeed);
	}

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
mat4x4 ModuleCamera3D::GetViewMatrix()
{
	return ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

void ModuleCamera3D::Zoom(const float& zoom_speed)
{
	Position -= Z * App->input->GetMouseZ() * zoomSpeed;
	this->zoomSpeed = zoom_speed;
}

//void ModuleCamera3D::Zoom()
//{
//	Position -= Z * App->input->GetMouseZ() * zoomSpeed;
//}

//void ModuleCamera3D::SetZoomSpeed(const float& zoom_speed)
//{
//	this->zoomSpeed = zoom_speed;
//}

//float ModuleCamera3D::GetZoomSpeed() const
//{
//	return zoomSpeed;
//}

bool  ModuleCamera3D::SaveState(JSON_Value* file) const
{


	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), "modules.Camera.name", buf);
	json_serialize_to_file(file, "Config.json");


	json_object_dotset_number(json_object(file), "modules.Camera.Position.x", (double)Position.x);
	json_object_dotset_number(json_object(file), "modules.Camera.Position.y", (double)Position.y);
	json_object_dotset_number(json_object(file), "modules.Camera.Position.z", (double)Position.z);

	json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.x", (double)X.x);
	json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.y", (double)X.y);
	json_object_dotset_number(json_object(file), "modules.Camera.Direction.X.z", (double)X.z);

	json_object_dotset_number(json_object(file), "modules.Camera.Direction.Y.x", (double)Y.x);
	json_object_dotset_number(json_object(file), "modules.Camera.Direction.Y.y", (double)Y.y);
	json_object_dotset_number(json_object(file), "modules.Camera.Direction.Y.z", (double)Y.z);

	json_object_dotset_number(json_object(file), "modules.Camera.Direction.Z.x", (double)Z.x);
	json_object_dotset_number(json_object(file), "modules.Camera.Direction.Z.y", (double)Z.y);
	json_object_dotset_number(json_object(file), "modules.Camera.Direction.Z.z", (double)Z.z);

	//call recalculateMatrix when after loading X Y Z


	json_serialize_to_file(file, "Config.json");

	App->ui->AppendToOutput(DEBUG_LOG("Saved Camera module."));


	return true;
}

bool  ModuleCamera3D::LoadState(JSON_Value* file)
{
	const char* n = json_object_dotget_string(json_object(file), "modules.Camera.name");

	App->ui->AppendToOutput(DEBUG_LOG("%s", n));

	return true;
}
