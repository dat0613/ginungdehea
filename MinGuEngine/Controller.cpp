#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"

Controller::Controller()
{
	direction = D3DXVECTOR2(0.0f, 0.0f);
	speed = 30.0f;
}

Controller::~Controller()
{

}

void Controller::Update()
{
	direction = D3DXVECTOR2(0.0f, 0.0f);
	if (InputManager::get()->GetKey(InputManager::KEY::W))
	{
		direction.y -= 1.0f;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::S))
	{
		direction.y += 1.0f;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::A))
	{
		direction.x -= 1.0f;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::D))
	{
		direction.x += 1.0f;
	}
	GetGameObject()->transform->position += direction * speed;
}
