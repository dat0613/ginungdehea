#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
private:



public:

	void Init(GameObject::TYPE type);
	void Update();
	void OnTriggerEnter(GameObject * obj);

	RECT GetCollisionRect();		//플레이어와 충돌체크를 할때 만 호출

};