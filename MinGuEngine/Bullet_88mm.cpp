#include "stdafx.h"
#include "Bullet_88mm.h"
#include "RigidBody2D.h"
#include "Timer.h"

void Bullet_88mm::Awake()
{
	animation->SetType(Animation::TYPE::Bullet_88mm);
	AddComponent<Timer>()->SetTimer(1000);
	transform->scale = 0.3f;
	SortingLayer = 5;
}

void Bullet_88mm::Update()
{
	transform->position += direction * 150.0f;
}

void Bullet_88mm::SetDir(D3DXVECTOR2 dir)
{
	direction = dir;
}

Bullet_88mm::Bullet_88mm()
{

}


Bullet_88mm::~Bullet_88mm()
{

}