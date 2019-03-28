#include "stdafx.h"
#include "Ground.h"
#include "RigidBody2D.h"


void Ground::Awake()
{
	AddComponent<RigidBody2D>()->bodyType = RigidBody2D::Static;
	animation->SetType(Animation::TYPE::Ground);
	transform->scale = 5.0f;
	boxcollider2d->SetColliderSize(860 * transform->scale, 170 * transform->scale);
	tag = Tag::ground;
}

void Ground::Update()
{

}

Ground::Ground()
{

}


Ground::~Ground()
{

}
