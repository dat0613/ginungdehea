#pragma once

#include "GameObject.h"
#include "Bullet_88mm.h"

class MiddleTank;
class MachineGun : public GameObject
{
private:

	int burst;
	clock_t lastShoot;
	clock_t coolTime;

public:
	::MiddleTank * tank;
	void Awake();
	void Update();
	void LateUpdate();
	MachineGun();
	~MachineGun();
	void Shot();
};

