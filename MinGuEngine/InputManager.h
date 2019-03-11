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

	bool isDown;		// 현재 버튼이 눌리는 중인지
	bool lastDown;		// 이전에 버튼이 눌렸었는지
	bool Down;			// 한번 눌림
	bool Up;			// 손을 땜
	InputManager::KEY key;
	int keyCode;

};