#include "Input.h"
#include "Camera.h"
#include "Info.h"

HWND Input::hwnd = nullptr;
vector<KeyState *> Input::keyVector = vector<KeyState *>();
D3DXVECTOR2 Input::mousePositionScreen = D3DXVECTOR2(0.0f, 0.0f);
D3DXVECTOR2 Input::mousePositionWorld = D3DXVECTOR2(0.0f, 0.0f);
bool Input::activate = true;

void Input::Init(HWND hwnd)
{
	Input::hwnd = hwnd;

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
	keyVector[KEY::Z]->keyCode = 'Z';
	keyVector[KEY::X]->keyCode = 'X';
	keyVector[KEY::C]->keyCode = 'C';
}

void Input::Update()
{
	if (!activate)
		return;

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

bool Input::GetKey(KEY key)
{
	return keyVector[key]->isDown;
}

bool Input::GetKeyDown(KEY key)
{
	return keyVector[key]->Down;
}

bool Input::GetKeyUp(KEY key)
{
	return keyVector[key]->Up;
}