#pragma once

#include "GameObject.h"
#include "MachineGun.h"

class MiddleTank : public GameObject
{
private:

public:

	MiddleTank();
	void Update();
	~MiddleTank();
	void OnCollisionStay2D();
	MachineGun * machineGun;
	
};