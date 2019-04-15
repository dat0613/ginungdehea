#pragma once
#include "GameObject.h"



class Enemy : public GameObject
{
public:
	
	void Awake();
	void Update();

	Enemy();
	~Enemy();
};