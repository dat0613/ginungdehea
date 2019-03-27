#include "stdafx.h"
#include "Bullet_88mm.h"
#include "RigidBody2D.h"
#include "Timer.h"

void Bullet_88mm::Awake()
{
	auto rigidbody = AddComponent<RigidBody2D>()->bodyType = RigidBody2D::BodyType::Kinematic;
	animation->SetType(Animation::TYPE::Bullet_88mm);
	AddComponent<Timer>()->SetTimer(2500);
	transform->scale = 0.3f;
	SortingLayer = 5;
}

void Bullet_88mm::Update()
{

}

Bullet_88mm::Bullet_88mm()
{

}


Bullet_88mm::~Bullet_88mm()
{

}
