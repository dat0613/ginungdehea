#include "Cube.h"

#include "Info.h"
#include "Controller.h"
#include "Camera.h"
#include "RigidBody2D.h"

Cube::Cube()
{
	AddComponent<RigidBody2D>();
	animation->SetType(Animation::TYPE::Cube);
	Camera::target = this;
	boxcollider2d->SetColliderSize(500, 500);
	//transform->position = { SCREENWIDTH * 0.5f, SCREENHEIGHT * 0.5f };
	AddComponent<Controller>();
}

void Cube::Update()
{
	//transform->rotation += 0.001f;

	if (InputManager::get()->GetKey(InputManager::KEY::LEFT))
	{
		Camera::degree -= 0.01f*1000;
	}

	if (InputManager::get()->GetKey(InputManager::KEY::RIGHT))
	{
		Camera::degree += 0.01f*1000;
	}

	if (InputManager::get()->GetKey(InputManager::KEY::DOWN))
	{
		Camera::scope -= 0.01f;
	}

	if (InputManager::get()->GetKey(InputManager::KEY::UP))
	{
		Camera::scope += 0.01f;
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