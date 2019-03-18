#include "GameManager.h"
#include "GraphicManager.h"
#include "InputManager.h"
#include "Info.h"
#include <ctime>
#include "Camera.h"
#include "Scene_Test.h"


GameManager::GameManager()
{
}

void GameManager::Init(HWND hwnd)
{
	this->hwnd = hwnd;

	if ((d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return;

	D3DPRESENT_PARAMETERS para;
	ZeroMemory(&para, sizeof(para));

	para.Windowed = true;
	para.AutoDepthStencilFormat = D3DFMT_D16;
	para.BackBufferFormat = D3DFMT_A8R8G8B8;
	para.SwapEffect = D3DSWAPEFFECT_DISCARD;
	para.BackBufferWidth = SCREENWIDTH;
	para.BackBufferHeight = SCREENHEIGHT;
	
	if (FAILED(d3d->CreateDevice(0,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&para,
		&device
	)))
		return;

	srand((unsigned)int(time(NULL)));

	GraphicManager::get()->Init(device);
	InputManager::get()->Init(hwnd);

	nowScene = new Scene_Test();
	nowScene->Init();
}

void GameManager::Update()
{
	InputManager::get()->Update();
	nowScene->AutoCollision();
	nowScene->AutoUpdate();
	nowScene->AutoLateUpdate();
	Camera::Update();

	if (InputManager::get()->GetKeyDown(InputManager::KEY::ESC))
		exit(1);
}


void GameManager::Render()
{
	if (device == NULL)
		return;
	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	if (SUCCEEDED(device->BeginScene()))
	{
		nowScene->AutoRender();
		device->EndScene();
	}

	device->Present(NULL, NULL, NULL, NULL);
}

GameManager::~GameManager()
{

}
