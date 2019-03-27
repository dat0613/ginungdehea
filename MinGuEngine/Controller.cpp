#include "Controller.h"
#include "Input.h"
#include "GameObject.h"
#include "Camera.h"
#include "Bullet_120mm.h"

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
	tank = (MiddleTank *)GetGameObject();
}


void Controller::Update()
{
	rigidbody2d->velocity.x = 0;
	float rotaionSpeed = 5.0f;

	float leftRotationLimit = -180.0f;
	float rightRotaionLimit = 0.0f;

	if (!rigidbody2d->isAir)
	{
		//rigidbody2d->velocity.y -= 50;
		if(rigidbody2d->lastGravity > 5.0f)
			Camera::Shake(rigidbody2d->lastGravity * 5.0f);
	}

	if (Input::GetKeyDown(Input::KEY::C))
	{
		rigidbody2d->velocity.y -= 50;
		//rigidbody2d->Collision();
		rigidbody2d->gravity = 0.0f;
	}

	if (Input::GetKey(Input::KEY::UP))
	{

	}

	if (Input::GetKey(Input::KEY::DOWN))
	{
		rigidbody2d->velocity.y += speed;
	}

	if (Input::GetKey(Input::KEY::LEFT))
	{
		rigidbody2d->velocity.x = -speed;

		if(tank->machineGun->transform->rotation - rotaionSpeed > leftRotationLimit)
			tank->machineGun->transform->rotation -= rotaionSpeed;
		else
			tank->machineGun->transform->rotation = leftRotationLimit;
		//GetGameObject()->flip = true;
	}

	if (Input::GetKey(Input::KEY::RIGHT))
	{
		rigidbody2d->velocity.x = speed;

		if (tank->machineGun->transform->rotation + rotaionSpeed < rightRotaionLimit)
			tank->machineGun->transform->rotation += rotaionSpeed;
		else
			tank->machineGun->transform->rotation = rightRotaionLimit;

		GetGameObject()->flip = false;
	}


	if (Input::GetKeyDown(Input::KEY::Z))
	{
		tank->machineGun->Shot();
	}


	if (Input::GetKeyDown(Input::KEY::X))
	{
		auto obj = Instantiate<Bullet_120mm>();
		auto gameObject = GetGameObject();
		int sign = (gameObject->flip) ? (-1) : (1);
		obj->SetDir(sign);
		obj->transform->position = gameObject->transform->position - gameObject->transform->center + D3DXVECTOR2(996 * sign + 20, 224);
		Camera::Shake(50);
	}
}
