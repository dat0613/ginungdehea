#include "stdafx.h"
#include "Cloud.h"


void Cloud::Awake()
{
	auto anim = (Animation::TYPE)(((int)Animation::TYPE::Cloud1) + rand() % 3);
	animation->SetType(anim);
	speed = 2 + rand() % 10;
	transform->position.x = rand() % 100000;
	transform->position.y = -2000 + rand() % 500;
}

void Cloud::Update()
{
	transform->position.x += speed;
}

Cloud::Cloud()
{
}


Cloud::~Cloud()
{
}
