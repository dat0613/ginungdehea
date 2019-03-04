#include "Wall.h"

void Wall::Init(GameObject::TYPE type)
{
	GameObject::Init(type);

	SetIsCollider(true);
	shadow = true;
}

void Wall::Update()
{

}

void Wall::OnTriggerEnter(GameObject * obj)
{
	
}

RECT Wall::GetCollisionRect()
{
	RECT rt;
	rt.left = position.x;
	rt.top = position.y + spriteSize.y * 0.6f;
	rt.right = position.x + spriteSize.x;
	rt.bottom = position.y + spriteSize.y;

	return rt;
}