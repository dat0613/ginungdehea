#pragma once

#include "Component.h"
#include "RigidBody2D.h"
#include "MiddleTank.h"

class Controller : public Component
{
private:

	D3DXVECTOR2 direction;
	float speed;
	RigidBody2D *rigidbody2d;
	MiddleTank *tank;

	clock_t lastShoot;
	clock_t coolTime;

	float leftRotationLimit;
	float rightRotaionLimit;
	int jumpCount;

public:

	Controller();
	~Controller();
	void Awake();
	void Update();
};