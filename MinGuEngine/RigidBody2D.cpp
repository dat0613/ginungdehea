#include "RigidBody2D.h"
#include "GameObject.h"

RigidBody2D::RigidBody2D()
{
	this->bodyType = BodyType::Dynamic;
	velocity = D3DXVECTOR2(0.0f, 0.0f);
	lastGravity = gravity = 0.0f;
	gravityAccel = 0.5f;
	gravityScale = 0.5f;
	isAir = true;
	isTrigger = false;
}

RigidBody2D::~RigidBody2D()
{

}

void RigidBody2D::Update()
{
	lastGravity = gravity;
	// Static 은 움직이지 않음
	if (bodyType == BodyType::Static)
		return;


	// Dynamic 은 중력의 영향을 받음
	if (bodyType == BodyType::Dynamic)
	{
		if (isAir)
		{
			velocity.y += gravity;
			gravity += gravityScale;
			//gravityScale += gravityAccel;
			//printf("%f\n", gravity);
		}
	}

	isAir = true;
	lastMovex = lastMovey = false;
}

void RigidBody2D::Collision()
{
	//velocity = D3DXVECTOR2(0.0f, 0.0f);

	velocity.y = 0.0f;
	gravity = 0.0f;
	gravityAccel = 0.5f;
	gravityScale = 0.5f;

	isAir = false;
}

void RigidBody2D::xMove()
{
	if (!lastMovex)
	{
		GetGameObject()->transform->position.x += velocity.x;
		lastMovex = true;
	}
}

void RigidBody2D::yMove()
{
	if (!lastMovey)
	{
		GetGameObject()->transform->position.y += velocity.y;
		lastMovey = true;
	}
}

void RigidBody2D::xMoveCancle()
{
	if (lastMovex)
	{
		GetGameObject()->transform->position.x -= velocity.x;
		lastMovex = false;
	}
}

void RigidBody2D::yMoveCancle()
{
	if (lastMovey)
	{
		GetGameObject()->transform->position.y -= velocity.y;
		lastMovey = false;
	}
}
