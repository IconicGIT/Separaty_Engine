#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "GameObject.h"

class Primitive;
class PhysBody3D;
class GameObject;

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

	Prim_Plane plane;
	Prim_Cube cube;
	Prim_Sphere sphere;
	Prim_Cylinder cil;

	GameObject* gameObject;

private:
	std::vector<Primitive*> primitives;
};
