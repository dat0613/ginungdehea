#include "Cube.h"

#include "Info.h"
#include "Controller.h"
#include "Camera.h"

Cube::Cube()
{
	AddComponent<Controller>();
	animation->SetType(Animation::TYPE::Cube);
	Camera::target = this;
	//transform->position = { SCREENWIDTH * 0.5f, SCREENHEIGHT * 0.5f };
}

void Cube::Update()
{
	//transform->rotation += 0.001f;

	if (InputManager::get()->GetKey(InputManager::KEY::MOUSE0))
	{
		Camera::degree -= 0.01f*100;
	}
	if (InputManager::get()->GetKey(InputManager::KEY::MOUSE1))
	{
		Camera::degree += 0.01f*100;
	}
}

Cube::~Cube()
{
	
}