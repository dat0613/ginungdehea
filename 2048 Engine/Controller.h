#pragma once

#include "GameObject.h"
#include "Object.h"

class Controller : public GameObject
{
private:

	::Object * obj;

	bool lastDrag;
	bool dragSuccess;
	bool Start;

	D3DXVECTOR2 dragStart;
	D3DXVECTOR2 dragEnd;

public:

	void Init(GameObject::TYPE type);
	void Update();

	void setObject(::Object * obj);

	

};