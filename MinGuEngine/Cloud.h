#pragma once
#include "GameObject.h"
class Cloud :
	public GameObject
{
public:
	void Awake();
	void Update();
	float speed;
	Cloud();
	~Cloud();
};

