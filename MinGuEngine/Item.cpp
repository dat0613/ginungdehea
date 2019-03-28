#include "Item.h"
#include "MiddleTank.h"
#include "ItemEffect.h"

void Item::Awake()
{
	val = 0;
	transform->scale = 0.5f;
	boxcollider2d->SetColliderSize(512 * transform->scale, 512 * transform->scale);
}

void Item::Update()
{
	transform->position.y += sin(D3DXToRadian(val += 5)) * 5;
	if (val > 360)
		val = 0;
}

void Item::SetType(Animation::TYPE type)
{
	animation->SetType(type);
}

void Item::OnCollisionStay2D(GameObject * obj)
{
	if (obj->tag == Tag::MiddleTank)
	{
		auto tank = ((::MiddleTank *)obj);
		destroy = true;
		if(animation->type == Animation::TYPE::SpeedUP)
		{ 
			tank->speed *= 1.5f;
		}
		if (animation->type == Animation::TYPE::RangeUP)
		{
			tank->bulletSpeed *= 1.3f;
		}
		if (animation->type == Animation::TYPE::DoubleJump)
		{
			
		}
	}
}

Item::Item()
{

}


Item::~Item()
{

}

void Item::OnDisable()
{
	Instantiate<ItemEffect>()->transform->position = transform->position;
}
