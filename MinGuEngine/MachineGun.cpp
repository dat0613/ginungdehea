#include "MachineGun.h"
#include "RigidBody2D.h"
#include "Bullet_88mm.h"
#include "MiddleTank.h"

void MachineGun::Awake()
{
	animation->SetType(Animation::TYPE::MachineGun);
	transform->center = { 47 * 0.5f , 47 * 0.5f };
	SortingLayer = 4;

	coolTime = 20;
	lastShoot = 0;
	burst = 0;
}

void MachineGun::Update()
{
	if (burst > 0 && coolTime + lastShoot < clock())
	{
		float three = -10;
		for (int i = 0; i < 3; i++)
		{
			auto rebound = (rand() % 3) - 1 + three;
			auto rad = D3DXToRadian(transform->rotation + rebound);
			auto barrel = animation->frameSize.x;
			auto muzzle = D3DXVECTOR2(cos(rad) * barrel, sin(rad) * barrel);
			auto direction = muzzle;
			D3DXVECTOR2 normal;
			D3DXVec2Normalize(&normal, &direction);

			auto bullet = Instantiate<Bullet_88mm>();
			bullet->SetDir(normal);
			bullet->transform->position = muzzle + transform->position;
			bullet->transform->rotation = transform->rotation + rebound;

			three += 10;
		}
		lastShoot = clock();
		burst--;
	}
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
	burst += 3;
}
