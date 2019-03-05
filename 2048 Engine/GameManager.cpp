#include "GameManager.h"
#include "GraphicManager.h"

GameManager::~GameManager()
{
	Release();
}

HRESULT GameManager::Init(HWND hwnd)
{
	this->hwnd = hwnd;

	if ((D3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)		//
		return E_FAIL;

	D3DPRESENT_PARAMETERS para;
	ZeroMemory(&para, sizeof(para));

	para.Windowed = true;										//â���
	para.AutoDepthStencilFormat = D3DFMT_D16;
	//para.MultiSampleType = D3DMULTISAMPLE_10_SAMPLES;
	para.BackBufferFormat = D3DFMT_A8R8G8B8;
	para.SwapEffect = D3DSWAPEFFECT_DISCARD;
	para.EnableAutoDepthStencil = true;
	para.BackBufferWidth = SCREENWIDTH;							//���� �ػ�
	para.BackBufferHeight = SCREENHEIGHT;						//���� �ػ�

	if (FAILED(D3d->CreateDevice(0,			//����̽� ����
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&para,
		&Device)))
		return E_FAIL;

	srand((unsigned)int(time(NULL)));

	return true;
}

void GameManager::Update()
{
	InputManager::GetInstance()->Update(hwnd);
	nowScene->Update();
	GraphicManager::GetInstance()->CameraUpdate();
	nowScene->Collision();

	if (InputManager::GetInstance()->OneClickKey(ESC))
		exit(1);
}

void GameManager::Render()
{
	if (Device == NULL)
		return;
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);		//ȭ�� ����

	if (SUCCEEDED(Device->BeginScene()))
	{
		if (nowScene != NULL)
		{
			nowScene->Render();		
		}
		Device->EndScene();
	}

	Device->Present(NULL, NULL, NULL, NULL);
}

void GameManager::Release()
{
	delete nowScene;
}

void GameManager::pushUpdateList(GameObject * obj)
{
	nowScene->pushUpdateList(obj);
}

LPDIRECT3DDEVICE9 GameManager::getDevice()
{
	return Device;
}

void GameManager::GameStart()
{
	nowScene = new Scene();	// �߻� Ŭ������. ���߿� Scene�� ��ӹ޴� Ŭ������ ������ ��.
	nowScene->Init();
}