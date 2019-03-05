#pragma once

#include <string>
#include <d3dx9.h>
#include <d3d.h>

using namespace std;

class FontEvent
{
private:

public:
	char * str;
	int x;
	int y;
	int size;

	D3DXCOLOR color;

	void Init(char * str, int x, int y, int size, D3DXCOLOR color);
	~FontEvent();
};