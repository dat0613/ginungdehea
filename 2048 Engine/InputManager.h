#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h> 
#include "Singleton.h"
#include "KeyboardEvent.h"
#include "GraphicManager.h"

#define LEFTMOUSE 0				//마우스 좌클릭
#define RIGHTMOUSE 1			//마우스 우클릭
#define LEFT 2					//방향키 왼쪽
#define RIGHT 3					//방향키 오른쪽
#define UP 4					//방향키 위쪽
#define DOWN 5					//방향키 아랫쪽

#define SKILL1 6				//스킬1 Q
#define SKILL2 7				//스킬2 E

#define ESC 8					//ESC
#define SPACE 9
#define RELOAD 10
#define F 11
#define G 12

//모든 키는 1차원 배열에서 관리할수 있게끔 해야함.

#define NUMOFKEY 13				//관리하는 키의 갯수에 맞게 설정

class InputManager : public Singleton <InputManager>
{
private:
	D3DXVECTOR2 mousePosition;
	KeyboardEvent keyEvent[NUMOFKEY];

public:
	void Init();
	void Update(HWND hwnd);

	bool isActive;
	
	D3DXVECTOR2 getMousePosition();
	D3DXVECTOR2 getMousePositionScreen();

	bool OneClickKey(int key);
	bool ClickKey(int key);

	void Release();
};