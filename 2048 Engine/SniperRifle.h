#pragma once

#include "Gun.h"

class SniperRifle :public Gun
{
private:

	D3DXVECTOR2 GetMuzzlePosition();
	D3DXVECTOR2 GetTargetPosition();

protected:

	void ReloadSound();

public:

	void Init(GameObject::TYPE type);
	void Update();
	bool Shoot();

	void OnTriggerEnter(GameObject * object);
};