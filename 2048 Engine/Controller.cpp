#include "Controller.h"
#include "InputManager.h"

void Controller::Init(GameObject::TYPE type)
{
	GameObject::Init(type);

	visible = false;

	lastDrag = false;
	Start = false;
	dragSuccess = false;

	dragStart = dragEnd = { 0.0f,0.0f };
}

void Controller::Update()
{

	if (InputManager::GetInstance()->ClickKey(LEFTMOUSE))
	{
		if (!Start)
		{
			dragStart = InputManager::GetInstance()->getMousePositionScreen();
			Start = true;
		}
		else
		{
			dragEnd = InputManager::GetInstance()->getMousePositionScreen();
		}
	}
	else
	{
		if (Start)
		{
			auto dif = dragStart - dragEnd;
			D3DXVECTOR2 normal;
			D3DXVec2Normalize(&normal, &dif);
			float length;
			length = D3DXVec2Length(&dif);

			obj->setSpeed(normal * length * 0.3f);

			Start = false;
		}
	}
	


	lastDrag = false;
}


void Controller::setObject(::Object * obj)
{
	this->obj = obj;
}
