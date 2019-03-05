#pragma once

#include "GameObject.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Singleton.h"
#include "head.h"
#include "Scene.h"

class GameManager : public Singleton <GameManager>
{
private:

	LPDIRECT3D9 D3d;
	LPDIRECT3DDEVICE9 Device;
	HWND hwnd;

	Scene * nowScene;

public:
	~GameManager();
	HRESULT Init(HWND hwnd);
	void Update();
	void Render();
	void Release();

	void pushUpdateList(GameObject * obj);
	LPDIRECT3DDEVICE9 getDevice();
	void GameStart();
	
};