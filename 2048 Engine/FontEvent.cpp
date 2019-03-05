#include "FontEvent.h"

void FontEvent::Init(char * str, int x, int y, int size, D3DXCOLOR color)
{

	int strLen = strlen(str) + 1;
	this->str = new char[strLen];
	//strcpy(this->str, str);
	strcpy_s(this->str, strLen, str);

	this->x = x;
	this->y = y;
	this->size = size;

	this->color = color;
}

FontEvent::~FontEvent()
{
	delete[] str;
}