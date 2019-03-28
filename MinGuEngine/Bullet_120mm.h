#pragma once
#include "GameObject.h"

class Bullet_120mm : public GameObject
{
private:

	int dir;

public:

	Bullet_120mm();
	~Bullet_120mm();
	float speed;
	void Awake();
	void Update();
	void OnDisable();
	void SetDir(int dir);
	void OnCollisionStay2D(GameObject * obj);

};