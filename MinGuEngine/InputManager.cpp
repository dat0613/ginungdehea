#include "InputManager.h"
#include "Camera.h"
#include "Info.h"

void InputManager::Init(HWND hwnd)
{
	this->hwnd = hwnd;

	keyVector.resize(KEY::MAXKEY, nullptr);

	for (auto &key : keyVector)
	{
		key = new KeyState();
		key->isDown = key->lastDown = key->Up = key->Down = false;
	}
	
	keyVector[KEY::MOUSE0]->keyCode = VK_LBUTTON;
	keyVector[KEY::MOUSE1]->keyCode = VK_RBUTTON;
	keyVector[KEY::W]->keyCode = 'W';
	keyVector[KEY::A]->keyCode = 'A';
	keyVector[KEY::S]->keyCode = 'S';
	keyVector[KEY::D]->keyCode = 'D';
	keyVector[KEY::LEFT]->keyCode = VK_LEFT;
	keyVector[KEY::RIGHT]->keyCode = VK_RIGHT;
	keyVector[KEY::UP]->keyCode = VK_UP;
	keyVector[KEY::DOWN]->keyCode = VK_DOWN;
	keyVector[KEY::SPACE]->keyCode = VK_SPACE;
	keyVector[KEY::ESC]->keyCode = VK_ESCAPE;

}

void InputManager::Update()
{
	for (auto key : keyVector)
	{
		key->isDown = key->Up = key->Down = false;

		key->isDown = (GetAsyncKeyState(key->keyCode) & 0x8000);
		if (key->isDown)
		{
			if (!key->lastDown)
				key->Down = true;
			key->lastDown = true;
		}
		else
		{
			if (key->lastDown)
				key->Up = true;
			key->lastDown = false;
		}
	}
	
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(hwnd, &mouse);
	mousePositionScreen = { (float)mouse.x, (float)mouse.y };
	mousePositionWorld = (mousePositionScreen + Camera::position) * Camera::scope;
	mousePositionWorld.x -= SCREENWIDTH * 0.5f;
	mousePositionWorld.y -= SCREENHEIGHT * 0.5f;
}

bool InputManager::GetKey(KEY key)
{
	return keyVector[key]->isDown;
}

bool InputManager::GetKeyDown(KEY key)
{
	return keyVector[key]->Down;
}

bool InputManager::GetKeyUp(KEY key)
{
	return keyVector[key]->Up;
}