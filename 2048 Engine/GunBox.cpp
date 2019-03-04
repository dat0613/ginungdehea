#include "GunBox.h"

void GunBox::Init(GameObject::TYPE type)
{
	GameObject::Init(type);
	shadow = true;
	SetIsCollider(true);
	gun = nullptr;
}

void GunBox::Update()
{
	if (gun != nullptr)
	{
		if (gun->GetIsPossessed())
		{
			gun->visible = true;
			enabled = false;
		}
	}
}

void GunBox::OnTriggerEnter(GameObject * obj)
{
	switch (obj->getType())
	{
	case GameObject::Player:
		enabled = false;

		if (gun != nullptr)
		{
			gun->visible = true;
		}

		break;
	}
}

Gun * GunBox::GetGun()
{
	return gun;
}

void GunBox::SetGun(Gun * gun)
{
	if(gun != nullptr)
		setPosition(gun->getPosition());
	this->gun = gun;
}
