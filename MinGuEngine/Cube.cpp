#include "Cube.h"

#include "Info.h"
#include "Controller.h"
#include "Camera.h"
#include "RigidBody2D.h"

Cube::Cube()
{
	AddComponent<RigidBody2D>()->bodyType = RigidBody2D::Dynamic;
	animation->SetType(Animation::TYPE::Cube);
	Camera::target = this;
	boxcollider2d->SetColliderSize(650, 380);
	//transform->position = { SCREENWIDTH * 0.5f, SCREENHEIGHT * 0.5f };
	AddComponent<Controller>();
}

void Cube::Update()
{
	//transform->rotation += 1.0f;

	if (Input::GetKey(Input::KEY::LEFT))
	{
		Camera::degree -= 0.01f * 1000;
	}

	if (Input::GetKey(Input::KEY::RIGHT))
	{
		Camera::degree += 0.01f * 1000;
	}

	if (Input::GetKey(Input::KEY::DOWN))
	{
		Camera::ZoomIn();
	}

	if (Input::GetKey(Input::KEY::UP))
	{
		Camera::ZoomOut();
	}

	if (transform->position.y > 10000)
	{
		transform->position = D3DXVECTOR2(0, -1000);
		GetComponent<RigidBody2D>()->velocity = { 0.0f,0.0f };
		Camera::Shake(250);
	}
}

Cube::~Cube()
{

}

void Cube::OnCollisionStay2D()
{

}