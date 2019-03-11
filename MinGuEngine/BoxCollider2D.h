#pragma once

#include "Component.h"


class BoxCollider2D : public Component
{
private:

public:

	BoxCollider2D();
	~BoxCollider2D();
	bool isTrigger;
	void Update();
	D3DXVECTOR2 size;

};