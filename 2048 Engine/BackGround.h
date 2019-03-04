#pragma once
#include "GameObject.h"

class BackGround : public GameObject
{
private:

public:

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};