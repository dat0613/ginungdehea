#pragma once

#include <vector>
#include <Windows.h>
#include <d3dx9.h>

using namespace std;

class KeyState;

static class Input
{
public:

	static enum KEY { MOUSE0,  MOUSE1, W, A, S, D,LEFT ,RIGHT, UP, DOWN, Z, X, C,  SPACE,ESC ,MAXKEY };

private:

	static HWND hwnd;
	static vector<KeyState *> keyVector;

public:

	static void Init(HWND hwnd);
	static void Update();

	static bool GetKey(KEY key);
	static bool GetKeyDown(KEY key);
	static bool GetKeyUp(KEY key);
	static D3DXVECTOR2 mousePositionScreen;
	static D3DXVECTOR2 mousePositionWorld;
	static bool activate;

};

class KeyState
{
public:

	bool isDown;		// ���� ��ư�� ������ ������
	bool lastDown;		// ������ ��ư�� ���Ⱦ�����
	bool Down;			// �ѹ� ����
	bool Up;			// ���� ��
	Input::KEY key;
	int keyCode;

};