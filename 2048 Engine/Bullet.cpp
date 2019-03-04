#include "Bullet.h"
#include "InputManager.h"
#include "SoundManager.h"

void Bullet::Init(GameObject::TYPE type)
{
	GameObject::Init(type);
	Direction = D3DXVECTOR2(0.0f, 0.0f);
	speed = 0.0f;
	effectiveRange = 0.0f;
	SetIsCanMove(true);
	//setSize(0.5f, 0.5f);

	//setSize(D3DXVECTOR2(0.5f, 0.5f));
}

void Bullet::Update()
{
	
	//static bool move = false;

	//if (InputManager::GetInstance()->OneClickKey(SKILL1))
	//{
	//	if(move)
	//		GraphicManager::GetInstance()->SetShake(5);
	//	if(!move)
	//		GraphicManager::GetInstance()->SetShake(10);
	//	
	//	move = !move;
	//}
	//
	//if (move)
		position += speed * Direction;

	D3DXVECTOR2 dif = position - StartPosition;

	if (D3DXVec2Length(&dif) > effectiveRange)
		enabled = false;
}

void Bullet::SetOption(int OwnerID,float speed, D3DXVECTOR2 targetPos,float effectiveRange,float power)
{
	this->OwnerID = OwnerID;
	this->speed = speed;
	StartPosition = position;

	//int punch = 100;

	//targetPos.x += ((rand() % punch) - punch * 0.5f);
	//targetPos.y += ((rand() % punch) - punch * 0.5f);
	this->power = power;
	D3DXVECTOR2 dif = targetPos - StartPosition;
	degree = D3DXToDegree(atan2(dif.y, dif.x));

	D3DXVec2Normalize(&Direction, &dif);
	this->effectiveRange = effectiveRange;
}

void Bullet::OnTriggerEnter(GameObject * Object)
{
	switch (Object->getType())
	{
	case GameObject::TYPE::Wall:
	case GameObject::TYPE::Test3:
	case GameObject::TYPE::PlayerNetwork:
	case GameObject::TYPE::Player:
		enabled = false;

			break;
	}
}

int Bullet::GetOwnerID()
{
	return OwnerID;
}

float Bullet::GetPower()
{
	return power;
}

D3DXVECTOR2 Bullet::GetDir()
{
	return Direction;
}
