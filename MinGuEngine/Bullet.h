#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:

	int dir;
	clock_t shootTime;

public:

	Bullet();
	~Bullet();
	void Awake();
	void Update();
	void SetDir(int dir);
	void OnCollisionStay2D(GameObject * obj);
};


