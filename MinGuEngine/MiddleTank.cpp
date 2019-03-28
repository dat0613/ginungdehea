#include "MiddleTank.h"

#include "Info.h"
#include "Controller.h"
#include "Camera.h"
#include "RigidBody2D.h"

MiddleTank::MiddleTank()
{
	AddComponent<RigidBody2D>()->bodyType = RigidBody2D::Dynamic;
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
}

void MiddleTank::Update()
{
	//transform->rotation += 1.0f;

	//if (Input::GetKey(Input::KEY::LEFT))
	//{
	//	Camera::degree -= 0.01f * 1000;
	//}

	//if (Input::GetKey(Input::KEY::RIGHT))
	//{
	//	Camera::degree += 0.01f * 1000;
	//}

	//if (Input::GetKey(Input::KEY::DOWN))
	//{
	//	Camera::ZoomOut();
	//}

	//if (Input::GetKey(Input::KEY::UP))
	//{
	//	Camera::ZoomIn();
	//}

	if (transform->position.y > 10000)
	{
		transform->position = D3DXVECTOR2(0, -1000);
		GetComponent<RigidBody2D>()->velocity = { 0.0f,0.0f };
		Camera::Shake(250);
	}
	// 370 190
	machineGun->transform->position = -transform->center + transform->position + D3DXVECTOR2(240, 260);
}

MiddleTank::~MiddleTank()
{

}

void MiddleTank::OnCollisionStay2D(GameObject * obj)
{

}