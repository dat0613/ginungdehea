#include "head.h"
#include "GameManager.h"
#include "GraphicManager.h"
#include "InputManager.h"

LRESULT CALLBACK WndProc(HWND  hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		InputManager::GetInstance()->Init();
		GameManager::GetInstance()->Init(hwnd);
		GraphicManager::GetInstance()->Init(GameManager::GetInstance()->getDevice());
		GameManager::GetInstance()->GameStart();
		break;

	case WM_PAINT:
		GameManager::GetInstance()->Render();
		break;

	case WM_GETMINMAXINFO:

		RECT rc;
		rc = { 0,0,SCREENWIDTH,SCREENHEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = rc.right - rc.left;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = rc.bottom - rc.top;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = rc.right - rc.left;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = rc.bottom - rc.top;
		return FALSE;
		break;

	case WM_ACTIVATEAPP:
		InputManager::GetInstance()->isActive = (bool)wParam;
		break;

	case WM_DESTROY:
		GameManager::GetInstance()->Release();
		InputManager::GetInstance()->Release();
		GraphicManager::GetInstance()->Release();

		_CrtDumpMemoryLeaks();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}