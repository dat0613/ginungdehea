#include "stdafx.h"
#include "Explosion.h"


void Explosion::Awake()
{
	animation->SetType(Animation::Explosion);
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
