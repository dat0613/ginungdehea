#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
private:



public:

	void Init(GameObject::TYPE type);
	void Update();
	void OnTriggerEnter(GameObject * obj);

	RECT GetCollisionRect();		//�÷��̾�� �浹üũ�� �Ҷ� �� ȣ��

};