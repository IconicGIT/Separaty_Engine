#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class Primitive;
class  PhysBody3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	//Draw 


	//TODO 9: Create an "OnCollision" method specific for this module

	Prim_Plane plane;
	Prim_Cube cube;
	Prim_Sphere sphere;
	Prim_Cylinder cil;

private:
	std::vector<Primitive*> primitives;
};
