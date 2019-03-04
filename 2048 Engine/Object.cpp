#include "Object.h"

void Object::Init(GameObject::TYPE type)
{
	GameObject::Init(type);
	speed = { 0.0f,0.0f };

	SetIsCanMove(true);
	lastCollisionObject = nullptr;
	lastCollision = false;
}

void Object::Update()
{
	auto vec = D3DXVec2Lerp(&speed, &speed, new D3DXVECTOR2(0.0f, 0.0f), 0.1f); 

	position += speed;

	if ((abs(speed.x) < 0.05f))
		speed.x = 0.0f;


	if ((abs(speed.y) < 0.05f))
		speed.y = 0.0f;

	if (lastCollision == false)
		lastCollisionObject = nullptr;


	lastCollision = false;
}

void Object::OnTriggerEnter(GameObject * obj)
{
	lastCollision = true;
	if (lastCollisionObject == obj)
		return;

	if (obj->getType() == GameObject::TYPE::Object)
	{
		auto object = (Object *)obj;
		auto object_speed = object->getSpeed();

		if (abs(speed.x) > abs(speed.y))
		{// x축 방향으로 이동 중임
			speed.x *= -0.5f;
		}
		else if(abs(speed.x - speed.y) < 0.001f)
		{// x = y
			speed *= -0.5f;
		}
		else
		{// y축 방향으로 이동 중임
			speed.y *= -0.5f;
		}

		speed -= object_speed;
	}
	
	lastCollisionObject = obj;
}

D3DXVECTOR2 Object::getSpeed()
{
	return speed;
}

void Object::setSpeed(float x, float y)
{
	setSpeed({ x,y });
}

void Object::setSpeed(D3DXVECTOR2 speed)
{
	this->speed = speed;
}
