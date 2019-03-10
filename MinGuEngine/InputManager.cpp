#include "InputManager.h"

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
	keyVector[KEY::SPACE]->keyCode = VK_SPACE;

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