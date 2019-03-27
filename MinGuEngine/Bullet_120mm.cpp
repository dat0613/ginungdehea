#include "Bullet_120mm.h"
#include "RigidBody2D.h"
#include "Explosion.h"
#include "Timer.h"

Bullet_120mm::Bullet_120mm()
{

}


Bullet_120mm::~Bullet_120mm()
{

}

void Bullet_120mm::Awake()
{
	auto rigidbody = AddComponent<RigidBody2D>();
	rigidbody->bodyType = RigidBody2D::Dynamic;
	rigidbody->isTrigger = false;
	animation->SetType(Animation::TYPE::Bullet_120mm);
	AddComponent<Timer>()->SetTimer(3000);

	transform->scale = 0.5f;

	boxcollider2d->SetColliderSize(476.0f * transform->scale, 83.0f * transform->scale);

	dir = 1;

}

void Bullet_120mm::Update()
{
	transform->position.x += 150.0f * dir;
}

void Bullet_120mm::OnDisable()
{
	Instantiate<Explosion>()->transform->position = transform->position;
}

void Bullet_120mm::SetDir(int dir)
{
	this->dir = dir;
	flip = (dir > 0) ? false : true;
}

void Bullet_120mm::OnCollisionStay2D(GameObject * obj)
{
	destroy = true;
}