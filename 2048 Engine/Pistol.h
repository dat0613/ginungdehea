#pragma once

#include "Gun.h"

class Pistol :public Gun
{

private:

	D3DXVECTOR2 GetTargetPosition();
	D3DXVECTOR2 GetMuzzlePosition();

protected:

	void ReloadSound();

public:

	void Init(GameObject::TYPE type);
	bool Shoot();
	void Update();


	void OnTriggerEnter(GameObject * obj);

};