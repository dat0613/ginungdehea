#include "GameObject.h"
#include "GameManager.h"
#include "GraphicManager.h"
#include "InputManager.h"

class GraphicManager;
class GameManager;

void GameObject::setSize(float x, float y)
{
	size.x = x;
	size.y = y;
}

void GameObject::setSize(D3DXVECTOR2 size)
{
	this->size = size;
}

D3DXVECTOR2 GameObject::getSize()
{
	return size;
}


void GameObject::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void GameObject::setPosition(D3DXVECTOR2 set)
{
	position = set;
}

float GameObject::getDegree()
{
	return degree;
}

void GameObject::setDegree(float degree)
{
	this->degree = degree;
}

GameObject::TYPE GameObject::getType()
{
	return type;
}

void GameObject::setType(TYPE type)
{
	this->type = type;
}

float GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(float velocity)
{
	this->velocity = velocity;
}

D3DXVECTOR2 GameObject::getSpriteSize()
{
	return spriteSize;
}

void GameObject::setSpriteSize(float x, float y)
{
	setSpriteSize(D3DXVECTOR2(x, y));
}

void GameObject::setSpriteSize(D3DXVECTOR2 size)
{
	spriteSize = size;
}

bool GameObject::GetIsCollier()
{
	return isCollider;
}

void GameObject::SetIsCollider(bool isCollider)
{
	this->isCollider = isCollider;

	if (isCanMove)
		isCanMove = isCollider;
}

bool GameObject::GetIsCanMove()
{
	return isCanMove;
}

void GameObject::SetIsCanMove(bool isCanMove)
{
	this->isCollider = isCanMove;
	this->isCanMove = isCanMove;
}

Animation& GameObject::GetAnimation()
{
	return animation;
}

void GameObject::SetAnimation(Animation::TYPE type)
{
	animation.SetType(type);
	spriteSize = animation.GetFrameSize();
}

D3DXVECTOR2 GameObject::getPosition()
{
	return position;
}


void GameObject::qsort(std::vector<D3DXVECTOR2>& v, std::vector<float>& radian_array, int s, int e)
{
	int bs = s, be = e;

	float pivot = radian_array[s];

	while (s < e)
	{
		while (pivot < radian_array[e] && s < e)
			e--;

		if (s > e)
			break;

		while (pivot >= radian_array[s] && s < e)
			s++;

		if (s > e)
			break;

		std::swap(radian_array[s], radian_array[e]);
		std::swap(v[s], v[e]);
	}

	std::swap(radian_array[bs], radian_array[s]);
	std::swap(v[bs], v[s]);

	if (bs < s)
		qsort(v, radian_array, bs, s - 1);
	if (be > e)
		qsort(v, radian_array, s + 1, be);
}

float GameObject::lerp(float p1, float p2, float d1)
{
	return (1 - d1) * p1 + d1 * p2;
}

bool GameObject::operator<(const GameObject & a)
{
	return this->zBuffer < a.zBuffer;
}

bool GameObject::operator<(const GameObject * a)
{
	return this->zBuffer < a->zBuffer;
}

void GameObject::UpdateZBuffer()
{
	if (!isUI)
		zBuffer = ((position.y + spriteSize.y) / 4000);
	else
		zBuffer = 1.0f;

	if (type == TestBackGround)
		zBuffer = 0.0001f;
}

void GameObject::Init(GameObject::TYPE type)
{
	this->type = type;

	size = D3DXVECTOR2(1.0f,1.0f);

	velocity = 0.0f;

	spriteSize = animation.GetFrameSize();

	degree = 0;

	isCollider = false;
	isCanMove = false;

	enabled = true;

	visible = true;
	zBuffer = 0.0f;
	shadow = false;
	isUI = false;

	color = D3DXCOLOR(255, 255, 255, 255);

	deltaTime = 0;
}

void GameObject::Update()
{

}

void GameObject::LateUpdate()
{

}

void GameObject::Render()
{

}

void GameObject::Release()
{

}

void GameObject::SetDeltaTime(clock_t delta)
{
	deltaTime = delta;
}

clock_t GameObject::GetDeltaTime()
{
	return deltaTime;
}

D3DXCOLOR GameObject::GetColor()
{
	return color;
}

void GameObject::SetColor(D3DXCOLOR color)
{
	this->color = color;
}

GameObject * Instantiate(GameObject::TYPE type)
{
	GameObject * gameObject = nullptr;

	switch (type)
	{

	}

	GameManager::GetInstance()->pushUpdateList(gameObject);

	return gameObject;
}

bool AABBCollision(GameObject * o1, GameObject * o2)
{
	auto o1_position = o1->getPosition();
	auto o1_size = o1->getSpriteSize();

	auto o2_position = o2->getPosition();
	auto o2_size = o2->getSpriteSize();

	if ((o1_position.x < o2_position.x + o2_size.x) &&
		(o1_position.y < o2_position.y + o2_size.y) &&
		(o1_position.x + o1_size.x > o2_position.x) &&
		(o1_position.y + o1_size.y > o2_position.y))
		return true;

	return false;
}


void GameObject::Destroy()
{
	enabled = false;
}

std::vector<D3DXVECTOR2> GameObject::GetVertices()
{
	std::vector <D3DXVECTOR2> vecArray(4);
	float theta = 0.0f;
	float len = 0.0f;

	//왼쪽 위 부터 시계방향 으로	0, 1
	//								3, 2
	//

	vecArray[0] = position;

	theta = D3DXToRadian(degree);
	vecArray[1] = D3DXVECTOR2(position.x + cos(theta) * spriteSize.x, position.y + sin(theta) * spriteSize.x);

	theta = D3DXToRadian(degree) + atan2(spriteSize.y, spriteSize.x);	//atan2 는 1번에서 3번 까지의 각도만큼을 더해줘야 했기 때문에 구한것임.
	len = D3DXVec2Length(&spriteSize);	//대각선의 길이
	vecArray[2] = D3DXVECTOR2(position.x + cos(theta) * len, position.y + sin(theta) * len);
	
	len *= 0.5f;

	D3DXVECTOR2 center = GetCenter();

	theta = D3DXToRadian(degree + 90);
	vecArray[3] = D3DXVECTOR2(position.x + cos(theta) * spriteSize.y, position.y + sin(theta) * spriteSize.y);

	std::vector<float> radian_vector(4);

	for (int i = 0; i < 4; i++)
	{
		auto dif = center - vecArray[i];
		radian_vector[i] = (atan2(dif.y, dif.x));
	} 

	qsort(vecArray, radian_vector, 0, vecArray.size() - 1);

	return vecArray;
}

D3DXVECTOR2 GameObject::GetCenter()
{
	auto theta = D3DXToRadian(degree) + atan2(spriteSize.y, spriteSize.x);	//atan2 는 1번에서 3번 까지의 각도만큼을 더해줘야 했기 때문에 구한것임.
	auto len = D3DXVec2Length(&spriteSize);	//대각선의 길이

	len *= 0.5f;

	auto center = D3DXVECTOR2(position.x + cos(theta) * len, position.y + sin(theta) * len);

	return center;
}

void GameObject::OnTriggerEnter(GameObject * obj)
{
	if (obj->getType() == GameObject::TYPE::Bullet)
	{
		enabled = false;
		GraphicManager::GetInstance()->AddShake(1);
	}
}

void Destroy(GameObject * obj)
{
	obj->enabled = false;
}
