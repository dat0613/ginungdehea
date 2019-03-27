#pragma once

#include "Component.h"

class Transform : public Component
{
private:



public:

	D3DXVECTOR2 position;
	float rotation;
	float scale;
	D3DXVECTOR2 center;

	Transform();
	void Update();
	void LateUpdate();
	~Transform();

};