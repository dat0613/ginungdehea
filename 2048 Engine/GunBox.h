#pragma once

#include "GameObject.h"

#include "Gun.h"

class GunBox :public GameObject
{
private:

	Gun * gun;

public:

	void Init(GameObject::TYPE type);
	void Update();

	void OnTriggerEnter(GameObject * obj);

	Gun * GetGun();
	void SetGun(Gun * gun);

};