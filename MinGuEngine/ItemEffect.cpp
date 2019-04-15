#include "stdafx.h"
#include "ItemEffect.h"


void ItemEffect::Awake()
{
	animation->SetType(Animation::TYPE::SpeedUpEffect);
	transform->scale = 2.0f;
}

void ItemEffect::Update()
{
	if (animation->end)
		destroy = true;
}

ItemEffect::ItemEffect()
{

}


ItemEffect::~ItemEffect()
{

}
