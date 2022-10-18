#ifndef __GameObject_H__
#define __GameObject_H__

#include "Module.h"
#include "Globals.h"

class GameObject : public Module
{
public:
	GameObject();
	~GameObject();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	/*bool ImportMesh();*/

private:

	unsigned int VAO;

	float *vertices;
};

#endif
