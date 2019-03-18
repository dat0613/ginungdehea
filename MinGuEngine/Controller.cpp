#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Camera.h"

Controller::Controller()
{
	direction = D3DXVECTOR2(0.0f, 0.0f);
	speed = 50.0f;
}

Controller::~Controller()
{

}

void Controller::Awake()
{
	rigidbody2d = GetGameObject()->GetComponent<RigidBody2D>();
}


void Controller::Update()
{
	rigidbody2d->velocity.x = 0;

	if (!rigidbody2d->isAir)
	{
		//rigidbody2d->velocity.y -= 50;
		//Camera::Shake(rigidbody2d->lastGravity * 10);
	}

	if (InputManager::get()->GetKeyDown(InputManager::KEY::W))
	{
		rigidbody2d->velocity.y -= 100;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::S))
	{
		rigidbody2d->velocity.y += speed;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::A))
	{
		rigidbody2d->velocity.x = -speed;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::D))
	{
		rigidbody2d->velocity.x = speed;
	}
}
