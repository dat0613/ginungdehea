#pragma once

#include "Component.h"
#include "RigidBody2D.h"

class Controller : public Component
{
private:

	D3DXVECTOR2 direction;
	float speed;
	RigidBody2D *rigidbody2d;

public:

	Controller();
	~Controller();
	void Awake();
	void Update();
};