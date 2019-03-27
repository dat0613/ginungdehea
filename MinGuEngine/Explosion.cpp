#include "stdafx.h"
#include "Explosion.h"


void Explosion::Awake()
{
	animation->SetType(Animation::Explosion);
	transform->rotation = rand() % 360;
	transform->scale = 2.0f;
}

void Explosion::Update()
{
	if (animation->end)
	{
		destroy = true;
	}
}

Explosion::Explosion()
{

}


Explosion::~Explosion()
{

}
