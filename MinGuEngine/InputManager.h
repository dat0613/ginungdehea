#pragma once

#include "Singleton.h"
#include <vector>
#include <Windows.h>
#include <d3dx9.h>

using namespace std;

class KeyState;

class InputManager : public Singleton<InputManager>
{
public:

	enum KEY { MOUSE0,  MOUSE1, W, A, S, D,LEFT ,RIGHT, UP, DOWN,  SPACE,ESC ,MAXKEY };

private:

	HWND hwnd;
	vector<KeyState *> keyVector;

public:

	void Init(HWND hwnd);
	void Update();

	bool GetKey(KEY key);
	bool GetKeyDown(KEY key);
	bool GetKeyUp(KEY key);
	D3DXVECTOR2 mousePositionScreen;
	D3DXVECTOR2 mousePositionWorld;

};

class KeyState
{
public:

	bool isDown;		// ���� ��ư�� ������ ������
	bool lastDown;		// ������ ��ư�� ���Ⱦ�����
	bool Down;			// �ѹ� ����
	bool Up;			// ���� ��
	InputManager::KEY key;
	int keyCode;

};