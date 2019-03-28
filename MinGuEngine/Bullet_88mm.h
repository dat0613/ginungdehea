#pragma once
#include "GameObject.h"
class Bullet_88mm :
	public GameObject
{
private:
	D3DXVECTOR2 direction;
public:

	void Awake();
	void Update();
	void SetDir(D3DXVECTOR2 dir);

	Bullet_88mm();
	~Bullet_88mm();
};

