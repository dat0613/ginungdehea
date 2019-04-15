#pragma once
#include "Enemy.h"
class UFOsimple :
	public Enemy
{
public:
	
	void Awake();
	void Update();

	int val;

	UFOsimple();
	~UFOsimple();
};

