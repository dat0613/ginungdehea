#include "stdafx.h"
#include "UFOsimple.h"


void UFOsimple::Awake()
{
	animation->SetType(Animation::TYPE::UFO1);
	val = 0;
}

void UFOsimple::Update()
{
	if (val > 360)
		val = 0;

	transform->position.y += sin(D3DXToRadian(val++));
	printf("%f\n", sin(D3DXToRadian(val++)));
}

UFOsimple::UFOsimple()
{
}


UFOsimple::~UFOsimple()
{
}
