#pragma once

#include "GameObject.h"

class MiddleTank;
class MachineGun : public GameObject
{
public:
	MiddleTank * tank;
	void Awake();
	void LateUpdate();
	MachineGun();
	~MachineGun();
	void Shot();
};

