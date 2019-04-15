#pragma once

#include "GameObject.h"
#include "MachineGun.h"
#include "RigidBody2D.h"

class MiddleTank : public GameObject
{
private:

public:

	MiddleTank();
	void Update();
	~MiddleTank();
	void Jump();
	float speed;
	float bulletSpeed;
	int jumpMaximum;
	int jumpCount;
	RigidBody2D * rigidbody;
	void OnCollisionStay2D(GameObject * obj);
	MachineGun * machineGun;

	bool tripleShot;
	clock_t tripleShotStart;
	clock_t tripleShotDuration;

	bool doubleJump;
	clock_t doubleJumpStart;
	clock_t doubleJumpDuration;
	
	void GetTripleShotItem();
	void GetDoubleJumpItem();
};