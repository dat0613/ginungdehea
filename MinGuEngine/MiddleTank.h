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
	float speed;
	float bulletSpeed;
	void OnCollisionStay2D(GameObject * obj);
	MachineGun * machineGun;
	
};