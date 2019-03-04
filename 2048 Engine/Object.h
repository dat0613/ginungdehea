#pragma once

#include "GameObject.h"

class Object : public GameObject
{
private:
	
	D3DXVECTOR2 speed;

	GameObject * lastCollisionObject;
	bool lastCollision;
	

public:

	void Init(GameObject::TYPE type);
	void Update();

	void OnTriggerEnter(GameObject * obj);

	D3DXVECTOR2 getSpeed();
	void setSpeed(float x, float y);
	void setSpeed(D3DXVECTOR2 speed);

};