#pragma once

#include "GameObject.h"
#include <d3dx9.h>

static class Camera
{
private:



public:

	static GameObject* target;
	static D3DXVECTOR2 position;
	static float scope;
	static float degree;
	static void Init();
	static void Update();
};