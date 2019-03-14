#pragma once

#include "GameObject.h"

class Cube : public GameObject
{
private:

public:

	Cube();
	void Update();
	~Cube();
	void OnCollisionStay2D();
};