#pragma once

#include "Singleton.h"
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "Scene.h"
#include "InputManager.h"

class GameManager : public Singleton<GameManager>
{
public:

	GameManager();
	void Init(HWND hwnd);
	void Update();
	void Render();
	~GameManager();

	Scene * nowScene;
private:


	
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 device;
	HWND hwnd;

};