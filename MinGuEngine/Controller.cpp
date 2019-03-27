#include "Controller.h"
#include "Input.h"
#include "GameObject.h"
#include "Camera.h"
#include "Bullet.h"

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
		if(rigidbody2d->lastGravity > 5.0f)
			Camera::Shake(rigidbody2d->lastGravity * 5.0f);
	}

	if (Input::GetKeyDown(Input::KEY::W))
	{
		rigidbody2d->velocity.y -= 50;
		//rigidbody2d->Collision();
		rigidbody2d->gravity = 0.0f;
	}
	if (Input::GetKey(Input::KEY::S))
	{
		rigidbody2d->velocity.y += speed;
	}
	if (Input::GetKey(Input::KEY::A))
	{
		rigidbody2d->velocity.x = -speed;
		GetGameObject()->flip = true;
	}
	if (Input::GetKey(Input::KEY::D))
	{
		rigidbody2d->velocity.x = speed;
		GetGameObject()->flip = false;
	}
	if (Input::GetKeyDown(Input::KEY::SPACE))
	{
		auto obj = Instantiate<Bullet>();
		auto gameObject = GetGameObject();
		int sign = (gameObject->flip) ? (-1) : (1);
		obj->SetDir(sign);
		obj->transform->position = gameObject->transform->position + D3DXVECTOR2(870 * sign, -70) * 0.5f;
		Camera::Shake(50);
	}
}
