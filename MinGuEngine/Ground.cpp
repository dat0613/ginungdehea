#include "stdafx.h"
#include "Ground.h"
#include "RigidBody2D.h"


void Ground::Awake()
{
	AddComponent<RigidBody2D>()->bodyType = RigidBody2D::Static;
	animation->SetType(Animation::TYPE::Ground);
	boxcollider2d->SetColliderSize(860, 170);
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
