#include "Negev.h"
#include "Controller.h"
#include "RigidBody2D.h"

Negev::Negev()
{
}

Negev::~Negev()
{

}

void Negev::Update()
{

}

void Negev::Awake()
{
	AddComponent<RigidBody2D>()->bodyType = RigidBody2D::BodyType::Static;
	animation->SetType(Animation::Negev);
	boxcollider2d->SetColliderSize(252, 352);
}
