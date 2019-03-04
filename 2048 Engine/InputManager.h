#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h> 
#include "Singleton.h"
#include "KeyboardEvent.h"
#include "GraphicManager.h"

#define LEFTMOUSE 0				//���콺 ��Ŭ��
#define RIGHTMOUSE 1			//���콺 ��Ŭ��
#define LEFT 2					//����Ű ����
#define RIGHT 3					//����Ű ������
#define UP 4					//����Ű ����
#define DOWN 5					//����Ű �Ʒ���

#define SKILL1 6				//��ų1 Q
#define SKILL2 7				//��ų2 E

#define ESC 8					//ESC
#define SPACE 9
#define RELOAD 10
#define F 11
#define G 12

//��� Ű�� 1���� �迭���� �����Ҽ� �ְԲ� �ؾ���.

#define NUMOFKEY 13				//�����ϴ� Ű�� ������ �°� ����

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