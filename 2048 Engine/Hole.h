#pragma once

#include "GameObject.h"

class Hole :public GameObject
{
private:

public:
	void Init(GameObject::TYPE type);
	void Update();
	void LateUpdate();

	void FastSetting(float x, float y, float width, float height);

	void OnTriggerEnter(GameObject * obj);
};