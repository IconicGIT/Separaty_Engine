#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "MathGeoLib.h"
#include "MathGeoLibFwd.h"
#include "GOC_Camera.h"

#include "GameObject.h"
#include "GameObjComponent.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	mat4x4 GetViewMatrix();

private:

	void CalculateViewMatrix();
	void Zoom(const float& zoom_speed);

	

	//void SetZoomSpeed(const float& zoom_speed);
	//float GetZoomSpeed() const;

	float zoomSpeed = 0.5f;

public:
	
	vec3 X, Y, Z, Position, currentReference, rotateAroundReference;

private:
	/*LCG lcg;*/
	mat4x4 ViewMatrix, ViewMatrixInverse;

	GOC_Camera* camera = nullptr;
};