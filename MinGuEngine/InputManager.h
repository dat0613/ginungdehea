#pragma once

#include "Singleton.h"
#include <vector>
#include <Windows.h>

using namespace std;

class KeyState;

class InputManager : public Singleton<InputManager>
{
public:

	enum KEY { MOUSE0,  MOUSE1, W, A, S, D,LEFT ,RIGHT,  SPACE ,MAXKEY };

private:

	HWND hwnd;
	vector<KeyState *> keyVector;

public:

	void Init(HWND hwnd);
	void Update();

	bool GetKey(KEY key);
	bool GetKeyDown(KEY key);
	bool GetKeyUp(KEY key);

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