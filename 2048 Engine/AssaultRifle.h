#pragma once

#include "Gun.h"

class AssaultRifle :public Gun
{
private:

	D3DXVECTOR2 GetTargetPosition();
	D3DXVECTOR2 GetMuzzlePosition();

protected:

	void ReloadSound();

public:

	void Init(GameObject::TYPE type);
	void Update();
	bool Shoot();

	void OnTriggerEnter(GameObject * object);

};