#pragma once
#include "GameObject.h"
class Item : public GameObject
{
public:

	float val;
	void Awake();
	void Update();
	void SetType(Animation::TYPE type);
	void OnCollisionStay2D(GameObject * obj);
	Item();
	~Item();
	void OnDisable();
};