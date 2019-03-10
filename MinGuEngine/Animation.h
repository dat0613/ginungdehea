#pragma once

#include "Component.h"

class Animation : public Component
{
public:
	enum TYPE {Cube, MAXANIMATION, NONE };


private:

	DWORD timePerFrame;
	DWORD lastFrameTime;

public:

	TYPE type;

	Animation();
	void Update();
	void LateUpdate();
	~Animation();

	D3DXVECTOR2 nowFrame;
	D3DXVECTOR2 imageSize;
	D3DXVECTOR2 frameSize;

	void SetType(TYPE type);
	TYPE GetType();

	D3DCOLOR color;
};