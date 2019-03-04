#pragma once

#include "GameObject.h"

class DieEffect : public GameObject
{
private:


public:

	void Init(GameObject::TYPE type);
	void Update();
	void LateUpdate();
};