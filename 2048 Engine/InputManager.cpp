#include "InputManager.h"

void InputManager::Init()
{
	mousePosition.x = mousePosition.y = 0;

	for (int i = 0;i < NUMOFKEY;i++)
		keyEvent[i].Init();
}

void InputManager::Update(HWND hwnd)
{
	if (!isActive)
		return;

	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hwnd, &pos);

	mousePosition.x = pos.x;
	mousePosition.y = pos.y;
}

D3DXVECTOR2 InputManager::getMousePosition()
{
	return mousePosition + GraphicManager::GetInstance()->GetCameraPosition();
}

D3DXVECTOR2 InputManager::getMousePositionScreen()
{
	return mousePosition;
}

bool InputManager::OneClickKey(int key)
{
	keyEvent[key].isClicked = ClickKey(key);

	if (keyEvent[key].isClicked == true)
	{
		if (keyEvent[key].oneClick == false)
		{
			keyEvent[key].oneClick = true;
			return true;
		}
	}
	else 
		keyEvent[key].oneClick = false;

	return false;
}

bool InputManager::ClickKey(int key)
{
	if (!isActive)
		return false;

	bool isClick = false;

	switch (key)
	{
	case LEFTMOUSE:
		isClick = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
		break;

	case RIGHTMOUSE:
		isClick = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
		break;

	case LEFT:
		isClick = (GetAsyncKeyState('A') & 0x8000);
		break;

	case RIGHT:
		isClick = (GetAsyncKeyState('D') & 0x8000);
		break;

	case UP:
		isClick = (GetAsyncKeyState('W') & 0x8000);
		break;

	case DOWN:
		isClick = (GetAsyncKeyState('S') & 0x8000);
		break;

	case SKILL1:
		isClick = (GetAsyncKeyState('Q') & 0x8000);
		break;

	case SKILL2:
		isClick = (GetAsyncKeyState('E') & 0x8000);
		break;

	case ESC:
		isClick = (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
		break;

	case SPACE:
		isClick = (GetAsyncKeyState(VK_SPACE) & 0x8000);
		break;

	case RELOAD:
		isClick = (GetAsyncKeyState('R') & 0x8000);
		break;

	case F:
		isClick = (GetAsyncKeyState('F') & 0x8000);
		break;

	case G:
		isClick = (GetAsyncKeyState('G') & 0x8000);
		break;
	}

	return isClick;
}

void InputManager::Release()
{
	
}
