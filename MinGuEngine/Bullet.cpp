#include "Bullet.h"
#include "RigidBody2D.h"
#include "Explosion.h"

Bullet::Bullet()
{

}


Bullet::~Bullet()
{

}

void Bullet::Awake()
{
	auto rigidbody = AddComponent<RigidBody2D>();
	rigidbody->bodyType = RigidBody2D::Dynamic;
	rigidbody->isTrigger = false;
	animation->SetType(Animation::TYPE::Bullet_120mm);

	transform->scale = 0.5f;

	boxcollider2d->SetColliderSize(476.0f * transform->scale, 83.0f * transform->scale);

	dir = 1;

	shootTime = clock();
}

void Bullet::Update()
{
	transform->position.x += 200.0f * dir;
	if (shootTime + 3000 < clock())
	{
		destroy = true;
		Instantiate<Explosion>()->transform->position = transform->position;
	}

	if (!GetComponent<RigidBody2D>()->isAir)
	{
		destroy = true;
		Instantiate<Explosion>()->transform->position = transform->position;
	}

	//printf("%f\n", transform->position.y);
}

void Bullet::SetDir(int dir)
{
	this->dir = dir;
	flip = (dir > 0) ? false : true;
}

void Bullet::OnCollisionStay2D(GameObject * obj)
{
	destroy = true;
	Instantiate<Explosion>()->transform->position = transform->position;
}