#include "Controller.h"
#include "Input.h"
#include "GameObject.h"
#include "Camera.h"
#include "Bullet_120mm.h"

Controller::Controller()
{
	direction = D3DXVECTOR2(0.0f, 0.0f);
}

Controller::~Controller()
{

}

void Controller::Awake()
{
	rigidbody2d = GetGameObject()->GetComponent<RigidBody2D>();
	tank = (MiddleTank *)GetGameObject();

	lastShoot = 0;
	coolTime = 1000;

	leftRotationLimit = -180.0f;
	rightRotaionLimit = 0.0f;
}


void Controller::Update()
{
	speed = tank->speed;
	rigidbody2d->velocity.x = 0;
	float rotationSpeed = 7.0f;
	float slope = 20.0f;

	if (!rigidbody2d->isAir)
	{
		//rigidbody2d->velocity.y -= 50;
		if (rigidbody2d->lastGravity > 5.0f)
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
		if (leftRotationLimit < -180.0f + slope)
			leftRotationLimit += rotationSpeed;
		else
			leftRotationLimit = -180.0f + slope;

		if (rightRotaionLimit > 0.0f - slope)
			rightRotaionLimit -= rotationSpeed;
		else
			rightRotaionLimit = 0.0f - slope;
	}
	else
	{
		leftRotationLimit = -180.0f;
		rightRotaionLimit = 0.0f;
	}

	if (Input::GetKey(Input::KEY::DOWN))
	{

	}

	if (Input::GetKey(Input::KEY::LEFT))
	{
		rigidbody2d->velocity.x = -speed;

		if (tank->machineGun->transform->rotation - rotationSpeed > leftRotationLimit)
			tank->machineGun->transform->rotation -= rotationSpeed;
		else
			tank->machineGun->transform->rotation = leftRotationLimit;
		//GetGameObject()->flip = true;
	}

	if (Input::GetKey(Input::KEY::RIGHT))
	{
		rigidbody2d->velocity.x = speed;

		if (tank->machineGun->transform->rotation + rotationSpeed < rightRotaionLimit)
			tank->machineGun->transform->rotation += rotationSpeed;
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
		if (lastShoot + coolTime < clock())
		{
			auto obj = Instantiate<Bullet_120mm>();
			obj->speed = tank->bulletSpeed;
			auto gameObject = GetGameObject();
			int sign = (gameObject->flip) ? (-1) : (1);
			obj->SetDir(sign);
			obj->transform->position = gameObject->transform->position - gameObject->transform->center + D3DXVECTOR2(996 * sign + 40, 57);
			Camera::Shake(50);

			lastShoot = clock();
		}
	}
}
