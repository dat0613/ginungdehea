#include "MiddleTank.h"

#include "Info.h"
#include "Controller.h"
#include "Camera.h"

MiddleTank::MiddleTank()
{
	rigidbody = AddComponent<RigidBody2D>();
	rigidbody->bodyType = RigidBody2D::Dynamic;

	animation->SetType(Animation::TYPE::MiddleTank);
	Camera::target = this;
	boxcollider2d->SetColliderSize(997, 363);
	//transform->position = { SCREENWIDTH * 0.5f, SCREENHEIGHT * 0.5f };
	machineGun = Instantiate<MachineGun>();
	machineGun->tank = this;

	AddComponent<Controller>();
	SortingLayer = 3;
	speed = 30.0f;
	bulletSpeed = 80.0f;
	
	tag = Tag::MiddleTank;

	jumpCount = jumpMaximum = 1;

	tripleShotDuration = 10000;
	doubleJumpDuration = 5000;
	tripleShotStart = doubleJumpStart = 0;
	tripleShot = doubleJump = false;
}

void MiddleTank::Update()
{
	auto curTime = clock();

	if (transform->position.y > 10000)
	{
		transform->position = D3DXVECTOR2(0, -1000);
		rigidbody->velocity = { 0.0f,0.0f };
		Camera::Shake(250);
		jumpCount = jumpMaximum;
	}

	if (!rigidbody->isAir)
	{
		//rigidbody2d->velocity.y -= 50;
		if (rigidbody->lastGravity > 1.0f)
		{
			Camera::Shake(rigidbody->lastGravity * 5.0f);
			jumpCount = jumpMaximum;
		}
	}

	if (tripleShot && tripleShotDuration + tripleShotStart < curTime)
	{
		tripleShot = false;
	}

	if (doubleJump && doubleJumpDuration + doubleJumpStart < curTime)
	{
		doubleJump = false;
		jumpMaximum = 1;
	}

	// 370 190
	machineGun->transform->position = -transform->center + transform->position + D3DXVECTOR2(240, 260);
}

MiddleTank::~MiddleTank()
{

}

void MiddleTank::Jump()
{
	if (jumpCount > 0)
	{
		rigidbody->velocity.y -= 50;
		rigidbody->gravity = 0.0f;

		jumpCount--;
	}
}

void MiddleTank::OnCollisionStay2D(GameObject * obj)
{

}

void MiddleTank::GetTripleShotItem()
{
	tripleShotStart = clock();
	tripleShot = true;
}

void MiddleTank::GetDoubleJumpItem()
{
	doubleJumpStart = clock();
	doubleJump = true;
	jumpMaximum = 2;
}