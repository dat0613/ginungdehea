#include "MachineGun.h"
#include "RigidBody2D.h"
#include "Bullet_88mm.h"
#include "MiddleTank.h"

void MachineGun::Awake()
{
	animation->SetType(Animation::TYPE::MachineGun);
	transform->center = { 47 * 0.5f , 47 * 0.5f };
	SortingLayer = 4;
}

void MachineGun::LateUpdate()
{
	//printf("%f\n", transform->rotation);
}

MachineGun::MachineGun()
{

}

MachineGun::~MachineGun()
{

}

void MachineGun::Shot()
{
	auto rad = D3DXToRadian(transform->rotation);
	auto barrel = animation->frameSize.x;
	auto muzzle = D3DXVECTOR2(cos(rad) * barrel, sin(rad) * barrel);
	auto direction = muzzle;
	D3DXVECTOR2 normal;
	D3DXVec2Normalize(&normal, &direction);

	auto bullet = Instantiate<Bullet_88mm>();
	auto rigidbody = bullet->GetComponent<RigidBody2D>();
	rigidbody->velocity = normal * 250;
	bullet->transform->position = muzzle + transform->position;
	bullet->transform->rotation = transform->rotation;
}
