#pragma once

#include "Component.h"


class BoxCollider2D : public Component
{
private:

public:

	BoxCollider2D();
	~BoxCollider2D();

	bool isTrigger;
	bool isUI;

	float radius;

	void Update();
	void SetColliderSize(D3DXVECTOR2 size);
	void SetColliderSize(float x, float y);
	D3DXVECTOR2 size;

};