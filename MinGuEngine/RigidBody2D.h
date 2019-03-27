#pragma once

#include "Component.h"

class RigidBody2D : public Component
{
private:



public:

	enum BodyType { Dynamic, Kinematic, Static };
	BodyType bodyType;
	D3DXVECTOR2 velocity;
	float gravity, gravityScale, gravityAccel, lastGravity;
	bool isAir;
	bool lastMovex;
	bool lastMovey;
	bool isTrigger;

	RigidBody2D();
	~RigidBody2D();
	void Update();
	void Collision();
	void xMove();
	void yMove();
	void xMoveCancle();
	void yMoveCancle();

};