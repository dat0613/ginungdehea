#pragma once

#include "Component.h"


class Controller : public Component
{
private:

	D3DXVECTOR2 direction;
	float speed;

public:

	Controller();
	~Controller();
	void Update();
};